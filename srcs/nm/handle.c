/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamhi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/24 15:35:58 by jcamhi            #+#    #+#             */
/*   Updated: 2017/07/24 15:35:59 by jcamhi           ###   ########.fr       */
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
	lc = (void*)(data->binary + offset) + sizeof(*header);
	i = 0;
	find_boundaries_64(data, offset);
	while (i < header->ncmds)
	{
		if (lc->cmd == LC_SYMTAB)
		{
			sc = (struct symtab_command*)lc;
			data->symoff = sc->symoff + offset;
			data->stroff = sc->stroff + offset;
			data->strsize = sc->strsize;
			data->nsyms = sc->nsyms;
			create_list_64(data, poids);
			return ;
		}
		lc = (void*)lc + lc->cmdsize;
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
	lc = (void*)(data->binary + offset) + sizeof(*header);
	i = 0;
	find_boundaries_32(data, offset);
	while (i < header->ncmds)
	{
		if (lc->cmd == LC_SYMTAB)
		{
			sc = (struct symtab_command*)lc;
			data->symoff = sc->symoff + offset;
			data->stroff = sc->stroff + offset;
			data->strsize = sc->strsize;
			data->nsyms = sc->nsyms;
			create_list_32(data, poids);
			return ;
		}
		lc = (void*)lc + lc->cmdsize;
		i++;
	}
}
