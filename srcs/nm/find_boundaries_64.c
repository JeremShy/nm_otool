#include <nm.h>

void	find_boundaries_64(t_data *data)
{
	struct mach_header_64			*header;
	struct load_command				*lc;
	struct segment_command_64	*sc;
	uint32_t									i;
	uint32_t									ns;

	header = (struct mach_header_64*)(data->binary);
	lc = (void*)(data->binary) + sizeof(*header);
	i = 0;
	ns = 1;
	data->sect_bss_beg = 0;
	data->sect_bss_end = 0;
	while (i < header->ncmds)
	{
		if (lc->cmd == LC_SEGMENT_64)
		{
			sc = (struct segment_command_64*)lc;
			if (ft_strequ(sc->segname, "__TEXT"))
			{
				data->begin_text = sc->vmaddr;
				if (sc->nsects == 0)
				{
					data->sect_text_beg = 0;
					data->sect_text_end = 0;
				}
				data->sect_text_beg = ns;
				data->sect_text_end = ns + sc->nsects - 1;
				data->end_text = sc->vmaddr + sc->vmsize;
			}
			else if (ft_strequ(sc->segname, "__DATA"))
			{
				data->begin_data = sc->vmaddr;
				if (sc->nsects == 0)
				{
					data->sect_data_beg = 0;
					data->sect_data_end = 0;
				}
				data->sect_data_beg = ns;
				data->sect_data_end = ns + sc->nsects - 1;
				data->end_data = sc->vmaddr + sc->vmsize;
			}
			else if (ft_strequ(sc->segname, "__BSS"))
			{
				data->begin_bss = sc->vmaddr;
				if (sc->nsects == 0)
				{
					data->sect_bss_beg = 0;
					data->sect_bss_end = 0;
				}
				data->sect_bss_beg = ns;
				data->sect_bss_end = ns + sc->nsects - 1;
				data->end_bss = sc->vmaddr + sc->vmsize;
			}
			ns += sc->nsects;
		}
		lc = (void*)lc + lc->cmdsize;
		i++;
	}
}
