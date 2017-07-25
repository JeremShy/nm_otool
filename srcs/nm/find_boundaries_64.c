/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_boundaries_64.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamhi <jcamhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/24 15:35:56 by jcamhi            #+#    #+#             */
/*   Updated: 2017/07/25 13:21:50 by jcamhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <nm.h>

static int	handle_seg_header_64(t_data *data, struct load_command *lc,
		uint32_t i)
{
	struct segment_command_64	*sc;
	struct section_64			*tab;
	uint32_t					j;

	j = 0;
	sc = (struct segment_command_64*)lc;
	tab = (void*)sc + sizeof(struct segment_command_64);
	if ((void*)sc > data->tend || (void*)tab > data->tend)
		return (-1);
	if (sc->nsects == 0)
		return (i);
	while (j < sc->nsects)
	{
		if ((void*)(tab + j) > data->tend)
			return (-1);
		data->nbsect++;
		if (ft_strequ(tab[j].sectname, "__text"))
			data->sections[j + i] = 'T';
		else if (ft_strequ(tab[j].sectname, "__bss"))
			data->sections[j + i] = 'B';
		else if (ft_strequ(tab[j].sectname, "__data"))
			data->sections[j + i] = 'D';
		else
			data->sections[j + i] = 'S';
		j++;
	}
	return (i + j);
}

int		find_boundaries_64(t_data *data, uint64_t offset)
{
	struct mach_header_64			*header;
	struct load_command				*lc;
	uint32_t						i;
	int32_t						j;

	header = (struct mach_header_64*)(data->binary + offset);
	lc = (void*)header + sizeof(struct mach_header_64);
	if ((void*)lc > data->tend)
		return (0);
	i = 0;
	j = 0;
	data->nbsect = 0;
	if (!(data->sections = (char*)malloc(header->ncmds * 20 + 1)))
		return (0);
	data->sections = ft_memset(data->sections, 'S', header->ncmds * 20);
	data->sections[header->ncmds] = '\0';
	while (i < header->ncmds)
	{
		if (lc->cmd == LC_SEGMENT_64)
		{
			j = handle_seg_header_64(data, lc, j);
			if (j == -1)
				return (0);
		}
		lc = (void*)lc + lc->cmdsize;
		if ((void*)lc > data->tend)
			return (0);
		i++;
	}
	return (1);
}
