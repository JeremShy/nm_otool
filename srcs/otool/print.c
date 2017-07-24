/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamhi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/24 15:36:46 by jcamhi            #+#    #+#             */
/*   Updated: 2017/07/24 15:36:47 by jcamhi           ###   ########.fr       */
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
		if (data->magic == MH_MAGIC)
			ft_printf("%08llx\t", print_size + offset);
		else if (data->magic == MH_MAGIC_64)
			ft_printf("%016llx\t", print_size + offset);
		i = 0;
		while (i < 0x10 && offset + i < size)
		{
			ft_printf("%02x ", *((unsigned char*)(start + offset + i)));
			i++;
		}
		offset += 0x10;
		ft_printf("\n");
	}
}
