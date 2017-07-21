#include <nm.h>

void	do_nm(const char *file)
{
	t_data			data;

	data.binary = map_binary(file);
	data.list = NULL;
	data.sections = NULL;
	data.av = file;
	if (!data.binary)
	{
		ft_putstr_fd("Error !!!\n", 2);
		return ;
	}
	data.magic = *(uint32_t*)(data.binary);
	if (data.magic == MH_MAGIC_64)
		handle_64(&data, 0, 0);
	else if (data.magic == MH_MAGIC)
		handle_32(&data, 0, 0);
	else if (data.magic == FAT_CIGAM)
		handle_fat_cigam(&data);
	else if (ft_strnequ((char*)data.binary, ARMAG, SARMAG))
		handle_static_lib(&data, 0);
	print_list(&data, data.list);
	delete_list(data.list);
	if (data.sections)
		free(data.sections);
	unmap_binary(file, data.binary);
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
			if (ac > 2)
				ft_printf("\n%s:\n", av[i]);
			do_nm(av[i]);
			i++;
		}
	}
	return (0);
}
