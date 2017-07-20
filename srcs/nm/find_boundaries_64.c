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
		return (i);
	while (j < sc->nsects)
	{
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

void	find_boundaries_64(t_data *data, uint64_t offset)
{
	struct mach_header_64			*header;
	struct load_command				*lc;
	uint32_t									i;
	uint32_t									j;
	// char											*ch;

	header = (struct mach_header_64*)(data->binary + offset);
	lc = (void*)header + sizeof(struct mach_header_64);
	i = 0;
	j = 0;
	data->nbsect = 0;
	if (!(data->sections = (char*)malloc(header->ncmds * 20 + 1)))
		return ;
	data->sections = ft_memset(data->sections, 'S', header->ncmds * 20);
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
}
