#include <nm.h>

int		ft_strequ(char const *s1, char const *s2)
{
	int		i;

	if ((!s1 && s2) || (s1 && !s2))
		return (0);
	if ((!s1 && !s2))
		return (1);
	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0')
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	if (s2[i] == s1[i])
		return (1);
	else
		return (0);
}

void	find_text_data_boundaries_64(t_data *data)
{
	struct mach_header_64			*header;
	struct load_command				*lc;
	struct segment_command_64	*sc;
	uint32_t									i;

	header = (struct mach_header_64*)(data->binary);
	lc = (void*)(data->binary) + sizeof(*header);
	i = 0;
	while (i < header->ncmds)
	{
		if (lc->cmd == LC_SEGMENT_64)
		{
			sc = (struct segment_command_64*)lc;
			if (ft_strequ(sc->segname, "__TEXT"))
			{
				data->begin_text = sc->vmaddr;
				data->end_text = sc->vmaddr + sc->vmsize;
			}
			else if (ft_strequ(sc->segname, "__DATA"))
			{
				data->begin_data = sc->vmaddr;
				data->end_data = sc->vmaddr + sc->vmsize;;
			}
		}
		lc = (void*)lc + lc->cmdsize;
		i++;
	}
}
