#include <nm.h>
#include <libbinary.h>

char	get_char_for_symtype(uint8_t type)
{
	if ((type | 0x0e) == N_UNDF)
		return ('U');
	else if ((type | 0x0e) == N_ABS)
		return ('A');
	return (' ');
}

void	output_64(uint32_t symoff, uint32_t stroff, uint32_t nsyms, char *binary)
{
	ft_printf("1\n");
	struct nlist_64 *array;
	char		*strings;
	uint32_t	i;

	array = (struct nlist_64*)((void*)binary + symoff);
	i = 0;
	strings = (char*)(binary + stroff);
	while(i < nsyms)
	{
		if (array[i].n_value)
			ft_printf("%016llx ", array[i].n_value);
		else
			ft_printf("%16c ", ' ');
		ft_printf("%s\n", strings + array[i].n_un.n_strx);
		i++;
	}
}

void	handle_64(char *binary)
{
	struct mach_header_64 *header;
	struct load_command	*lc;
	struct symtab_command	*sc;
	uint32_t			i;

	header = (struct mach_header_64*)binary;
	lc = (void*)binary + sizeof(*header);
	i = 0;
	while (i < header->ncmds)
	{
		if (lc->cmd == LC_SYMTAB)
		{
			sc = (struct symtab_command*)lc;
			output_64(sc->symoff, sc->stroff, sc->nsyms, binary);
			return ;
		}
		lc = (void*)lc + lc->cmdsize;
		i++;
	}
}

void	do_nm(const char *file)
{
	char	*binary;
	uint32_t		magic;

	binary = map_binary(file);
	if (!binary)
	{
		ft_printf("Error !!!\n");
		return ;
	}
	magic = *(int*)binary;
	if (magic == MH_MAGIC_64)
	{
		handle_64(binary);
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
