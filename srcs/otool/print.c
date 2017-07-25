/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamhi <jcamhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/24 15:36:46 by jcamhi            #+#    #+#             */
/*   Updated: 2017/07/25 17:53:16 by jcamhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <otool.h>

void	print(t_data *data, void *start, uint64_t size, uint64_t print_size)
{
	uint64_t	offset;
	int			i;

	ft_printf("Contents of (__TEXT,__text) section\n");
	offset = 0;
	i = 0;
	while (offset < size)
	{
		if (offset > (uint64_t)data->size)
			return (set_error_and_return(data));
		if (data->magic == MH_MAGIC || data->magic == MH_CIGAM)
			ft_printf("%08llx\t", print_size + offset);
		else if (data->magic == MH_MAGIC_64)
			ft_printf("%016llx\t", print_size + offset);
		i = 0;
		while (i < 0x10 && offset + i < size && offset + i < (uint64_t)data->size)
		{
			if (data->magic == MH_CIGAM)
				ft_printf("%02x", *((unsigned char*)(start + offset + i)));
			else
				ft_printf("%02x ", *((unsigned char*)(start + offset + i)));
			i++;
			if (data->magic == MH_CIGAM && i % 4 == 0)
				ft_printf(" ");
		}
		if (offset > (uint64_t)data->size)
			return (set_error_and_return(data));
		offset += 0x10;
		ft_printf("\n");
	}
}
