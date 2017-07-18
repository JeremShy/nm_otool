#include <nm.h>

static int	handle_seg_header_64(t_data *data, struct load_command *lc, uint32_t i)
{
	struct segment_command_64	*sc;
	struct section_64				*tab;
	uint32_t	j;

	j = 0;
	sc = (struct segment_command_64*)lc;
	tab = (void*)sc + sizeof(struct segment_command_64);
	if (sc->nsects == 0)
	{
		// // ft_printf("sc->segname : %s\n", sc->segname);
		// if (ft_strequ(sc->segname, "__TEXT"))
		// 	data->sections[j + i] = 'T';
		// else if (ft_strequ(sc->segname, "__DATA"))
		// 	data->sections[j + i] = 'D';
		// else if (ft_strequ(sc->segname, "__BSS"))
		// 	data->sections[j + i] = 'B';
		// else
		// 	data->sections[j + i] = 'S';
		return (i);
	}
	while (j < sc->nsects)
	{
		// ft_printf("tab[j].segname : %s\n", tab[j].segname);
		if (ft_strequ(tab[j].segname, "__TEXT"))
			data->sections[j + i] = 'T';
		else if (ft_strequ(tab[j].segname, "__DATA") && !ft_strequ(tab[j].sectname, "__common"))
			data->sections[j + i] = 'D';
		else if (ft_strequ(tab[j].segname, "__BSS"))
			data->sections[j + i] = 'B';
		else
			data->sections[j + i] = 'S';
		j++;
	}
	return (i + j);
}

void	find_boundaries_64(t_data *data)
{
	struct mach_header_64			*header;
	struct load_command				*lc;
	uint32_t									i;
	uint32_t									j;
	// char											*ch;

	header = (struct mach_header_64*)(data->binary);
	lc = (void*)(data->binary) + sizeof(*header);
	i = 0;
	j = 0;
	if (!(data->sections = (char*)malloc(header->ncmds + 1)))
		return ;
	data->sections = ft_memset(data->sections, 'S', header->ncmds);
	data->sections[header->ncmds] = '\0';
	while (i < header->ncmds)
	{
		if (lc->cmd == LC_SEGMENT_64)
		{
			j = handle_seg_header_64(data, lc, j);
		}
		lc = (void*)lc + lc->cmdsize;
		i++;
	}
	// write(1, data->sections, j);
	// write(1, "\n", 1);
	// if ((ch = ft_strrchr(data->sections, 'D')))
	// 	*ch = 'S';
}
