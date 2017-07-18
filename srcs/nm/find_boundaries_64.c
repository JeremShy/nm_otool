#include <nm.h>

void	find_boundaries_64(t_data *data)
{
	struct mach_header_64			*header;
	struct load_command				*lc;
	struct segment_command_64	*sc;
	uint32_t									i;
	// char											*ch;

	header = (struct mach_header_64*)(data->binary);
	lc = (void*)(data->binary) + sizeof(*header);
	i = 0;
	if (!(data->sections = (char*)malloc(header->ncmds + 1)))
		return ;
	data->sections = ft_memset(data->sections, 'S', header->ncmds);
	data->sections[header->ncmds] = '\0';
	while (i < header->ncmds)
	{
		if (lc->cmd == LC_SEGMENT_64)
		{
			sc = (struct segment_command_64*)lc;
			if (ft_strequ(sc->segname, "__TEXT"))
				data->sections[i] = 'T';
			else if (ft_strequ(sc->segname, "__DATA"))
				data->sections[i] = 'D';
			else if (ft_strequ(sc->segname, "__BSS"))
				data->sections[i] = 'B';
		}
		lc = (void*)lc + lc->cmdsize;
		i++;
	}
	// if ((ch = ft_strrchr(data->sections, 'D')))
	// 	*ch = 'S';
}
