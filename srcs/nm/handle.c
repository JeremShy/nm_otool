/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamhi <jcamhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/24 15:35:58 by jcamhi            #+#    #+#             */
/*   Updated: 2017/07/25 13:25:33 by jcamhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <nm.h>

void	handle_64(t_data *data, uint64_t offset, size_t poids)
{
	struct mach_header_64	*header;
	struct load_command		*lc;
	struct symtab_command	*sc;
	uint32_t				i;

	header = (struct mach_header_64*)(data->binary + offset);
	lc = (void*)(data->binary + offset) + sizeof(struct mach_header_64);
	i = 0;
	if ((void*)header > data->tend || (void*)lc > data->tend || find_boundaries_64(data, offset) == 0)
	{
		data->error = 1;
		return;
	}
	while (i < header->ncmds)
	{
		if (lc->cmd == LC_SYMTAB)
		{
			sc = (struct symtab_command*)lc;
			data->symoff = sc->symoff + offset;
			data->stroff = sc->stroff + offset;
			data->strsize = sc->strsize;
			data->nsyms = sc->nsyms;
			if (create_list_64(data, poids) == 0)
				data->error = 1;
			return ;
		}
		lc = (void*)lc + lc->cmdsize;
		if ((void*)lc > data->tend)
		{
			data->error = 1;
			return ;
		}
		i++;
	}
}

void	handle_32(t_data *data, uint64_t offset, size_t poids)
{
	struct mach_header		*header;
	struct load_command		*lc;
	struct symtab_command	*sc;
	uint32_t				i;

	header = (struct mach_header*)(data->binary + offset);
	lc = (void*)(data->binary + offset) + sizeof(struct mach_header);
	i = 0;
	if ((void*)header > data->tend || (void*)lc > data->tend || find_boundaries_32(data, offset) == 0)
	{
		data->error = 1;
		return ;
	}
	while (i < header->ncmds)
	{
		if (get_good_endian(*data, lc->cmd) == LC_SYMTAB)
		{
			sc = (struct symtab_command*)lc;
			data->symoff = get_good_endian(*data, sc->symoff) + offset;
			data->stroff = get_good_endian(*data, sc->stroff) + offset;
			data->strsize = get_good_endian(*data, sc->strsize);
			data->nsyms = get_good_endian(*data, sc->nsyms);
			if (create_list_32(data, poids) == 0)
				data->error = 1;
			return ;
		}
		lc = (void*)lc + get_good_endian(*data, lc->cmdsize);
		if ((void*)lc > data->tend)
		{
			data->error = 1;
			return ;
		}
		i++;
	}
}
