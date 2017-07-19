#include <nm.h>

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
		handle_64(&data, 0);
	else if (data.magic == MH_MAGIC)
		handle_32(&data, 0);
	else if (data.magic == FAT_CIGAM)
		handle_fat_cigam(&data);
	print_list(&data, data.list);
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
