#include <nm.h>


void	output_64(t_data *data)
{
	struct nlist_64 *array;
	char		*strings;
	uint32_t	i;

	array = (struct nlist_64*)((void*)(data->binary) + data->symoff);
	i = 0;
	strings = (char*)((data->binary) + data->stroff);
	data->list = NULL;
	while(i < data->nsyms)
	{
		data->list = add_elem_end(data, data->list, (uint64_t)(data->symoff + i * sizeof(struct nlist_64)));
		i++;
	}
	data->list = ft_sort(data->list);
	print_list(data, data->list);
}

void	handle_64(t_data *data)
{
	struct mach_header_64 *header;
	struct load_command	*lc;
	struct symtab_command	*sc;
	uint32_t			i;

	header = (struct mach_header_64*)(data->binary);
	lc = (void*)(data->binary) + sizeof(*header);
	i = 0;
	find_boundaries_64(data);
	while (i < header->ncmds)
	{
		if (lc->cmd == LC_SYMTAB)
		{
			sc = (struct symtab_command*)lc;
			data->symoff = sc->symoff;
			data->stroff = sc->stroff;
			data->strsize = sc->strsize;
			data->nsyms = sc->nsyms;
			output_64(data);
			return ;
		}
		lc = (void*)lc + lc->cmdsize;
		i++;
	}
}

void	do_nm(const char *file)
{
	t_data			data;

	data.binary = map_binary(file);
	data.list = NULL;
	if (!data.binary)
	{
		ft_printf("Error !!!\n");
		return ;
	}
	data.magic = *(uint32_t*)(data.binary);
	if (data.magic == MH_MAGIC_64)
	{
		handle_64(&data);
	}
}

int		main(int ac, char **av)
{
	int		i;

	if (ac == 1)
		do_nm("a.out");
	else
	{
		i = 1;
		while(i < ac)
		{
			do_nm(av[i]);
			i++;
		}
	}
	return (0);
}
