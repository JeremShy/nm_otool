/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamhi <jcamhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/24 15:36:01 by jcamhi            #+#    #+#             */
/*   Updated: 2017/07/25 15:26:13 by jcamhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <nm.h>

static int	init_data(t_data *data, const char *file)
{
	data->binary = map_binary(file, &(data->size));
	if (!data->binary)
	{
		ft_putstr_fd("Error !!!\n", 2);
		return (0);
	}
	data->tend = data->binary + data->size;
	data->error = 0;
	data->list = NULL;
	data->sections = NULL;
	data->av = file;
	data->endiancast = 0;
	data->magic = *(uint32_t*)(data->binary);
	return (1);
}

void		do_nm(const char *file, t_opt opt)
{
	t_data			data;

	if (!init_data(&data, file))
		return ;
	if (data.magic == MH_MAGIC_64)
		handle_64(&data, 0, 0);
	else if (data.magic == MH_MAGIC)
		handle_32(&data, 0, 0);
	else if (data.magic == FAT_CIGAM)
		handle_fat_cigam(&data, opt);
	else if (ft_strnequ((char*)data.binary, ARMAG, SARMAG))
		handle_static_lib(&data, 0, opt);
	if (data.error)
	{
		ft_putstr_fd("Error !!!\n", 2);
		return ;
	}
	if (data.list)
	{
		print_list(&data, data.list, opt);
		delete_list(data.list);
	}
	if (data.sections)
		free(data.sections);
	unmap_binary(data.binary, data.size);
}

int			main(int ac, char **av)
{
	int		i;
	t_opt	opt;

	ft_bzero((void*)(&opt), sizeof(t_opt));
	if (!ft_parsing(ac, av, &opt))
		return (1);
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
