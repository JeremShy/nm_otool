#include <nm.h>

void	do_nm(const char *file, t_opt opt)
{
	t_data			data;

	data.binary = map_binary(file);
	if (!data.binary)
	{
		ft_putstr_fd("Error !!!\n", 2);
		return ;
	}
	data.list = NULL;
	data.sections = NULL;
	data.av = file;
	data.magic = *(uint32_t*)(data.binary);
	if (data.magic == MH_MAGIC_64)
		handle_64(&data, 0, 0);
	else if (data.magic == MH_MAGIC)
		handle_32(&data, 0, 0);
	else if (data.magic == FAT_CIGAM)
		handle_fat_cigam(&data, opt);
	else if (ft_strnequ((char*)data.binary, ARMAG, SARMAG))
		handle_static_lib(&data, 0, opt);
	print_list(&data, data.list, opt);
	delete_list(data.list);
	if (data.sections)
		free(data.sections);
	unmap_binary(file, data.binary);
}

int		main(int ac, char **av)
{
	int		i;
	t_opt	opt;

	ft_bzero((void*)(&opt), sizeof(t_opt));
	opt = ft_parsing(ac, av);
	i = find_start(ac, av);
	if (ac == i)
		do_nm("a.out", opt);
	else
	{
		while (i < ac)
		{
			if (ac > 2)
				ft_printf("\n%s:\n", av[i]);
			do_nm(av[i], opt);
			i++;
		}
	}
	return (0);
}
