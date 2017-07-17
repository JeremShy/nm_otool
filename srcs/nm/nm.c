#include <nm.h>

char	get_char_for_symtype(struct nlist_64 elem, t_data data)
{
	if ((elem.n_type | 0x0e) == N_UNDF)
		return ('U');
	else if ((elem.n_type | 0x0e) == N_ABS)
		return ('A');
	else if ((elem.n_type | 0x0e) == N_SECT)
	{
		(void)data;
	}
	return (' ');
}

void	output_64(uint32_t symoff, uint32_t stroff, uint32_t nsyms, t_data *data)
{
	ft_printf("1\n");
	struct nlist_64 *array;
	char		*strings;
	uint32_t	i;

	array = (struct nlist_64*)((void*)(data->binary) + symoff);
	i = 0;
	strings = (char*)((data->binary) + stroff);
	while(i < nsyms)
	{
		if (array[i].n_un.n_strx != 0)
		{
			if (array[i].n_value)
				ft_printf("%016llx ", array[i].n_value);
			else
				ft_printf("%16c ", ' ');
			ft_printf("%c ", get_char_for_symtype(array[i], *data));
			ft_printf("%s\n", strings + array[i].n_un.n_strx);
		}
		i++;
	}
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
	find_text_data_boundaries_64(data);
	while (i < header->ncmds)
	{
		if (lc->cmd == LC_SYMTAB)
		{
			sc = (struct symtab_command*)lc;
			output_64(sc->symoff, sc->stroff, sc->nsyms, data);
			return ;
		}
		lc = (void*)lc + lc->cmdsize;
		i++;
	}
}

void	do_nm(const char *file)
{
	t_data			data;
	uint32_t		magic;

	data.binary = map_binary(file);
	if (!data.binary)
	{
		ft_printf("Error !!!\n");
		return ;
	}
	magic = *(int*)(data.binary);
	if (magic == MH_MAGIC_64)
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
