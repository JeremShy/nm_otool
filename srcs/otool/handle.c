#include <otool.h>

void	handle_lc_seg_64(t_data *data, uint64_t offset, uint64_t tot_offset)
{
	struct segment_command_64	*seg;
	struct section_64					*sect;
	uint32_t	i;

	seg = data->binary + offset;
	if (ft_strequ(seg->segname, "__TEXT"))
	{
		sect = (void*)seg + sizeof(struct segment_command_64);
		i = 0;
		while (i < seg->nsects)
		{
			if (ft_strequ(sect->sectname, "__text"))
			{
				print(data, data->binary + sect->offset + tot_offset, sect->size, sect->addr);
			}
			sect++;
			i++;
		}
	}
}

void	handle_64(t_data *data, uint64_t offset)
{
	struct load_command	*lc;
	struct mach_header_64	*header;
	uint32_t		i;

	header = data->binary + offset;
	lc = data->binary + offset + sizeof(struct mach_header_64);
	i = 0;
	while (i < header->ncmds)
	{
		if (lc->cmd == LC_SEGMENT_64)
			handle_lc_seg_64(data, (void*)lc - data->binary, offset);
		lc = (void*)lc + lc->cmdsize;
		i++;
	}
}

void	handle_lc_seg_32(t_data *data, uint64_t offset, uint64_t tot_offset)
{
	struct segment_command	*seg;
	struct section					*sect;
	uint32_t	i;

	seg = data->binary + offset;
	if (ft_strequ(seg->segname, "__TEXT"))
	{
		sect = (void*)seg + sizeof(struct segment_command);
		i = 0;
		while (i < seg->nsects)
		{
			if (ft_strequ(sect->sectname, "__text"))
			{
				print(data, data->binary + sect->offset + tot_offset, sect->size, sect->addr);
			}
			sect++;
			i++;
		}
	}
}

void	handle_32(t_data *data, uint64_t offset)
{
	struct load_command	*lc;
	struct mach_header	*header;
	uint32_t		i;

	header = data->binary + offset;
	lc = data->binary + offset + sizeof(struct mach_header);
	i = 0;
	while (i < header->ncmds)
	{
		if (lc->cmd == LC_SEGMENT)
			handle_lc_seg_32(data, (void*)lc - data->binary, offset);
		lc = (void*)lc + lc->cmdsize;
		i++;
	}
}
