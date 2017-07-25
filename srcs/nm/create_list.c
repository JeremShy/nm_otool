/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamhi <jcamhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/24 15:35:51 by jcamhi            #+#    #+#             */
/*   Updated: 2017/07/24 23:50:52 by jcamhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <nm.h>

void	create_list_64(t_data *data, size_t poids)
{
	uint32_t		i;

	i = 0;
	data->list = NULL;
	while (i < data->nsyms)
	{
		if ((void*)(data->symoff + i * sizeof(struct nlist_64)) > data->binary + data->size)
			return ;
		data->list = add_elem_end(data, data->list, (uint64_t)(data->symoff +
					i * sizeof(struct nlist_64)), poids);
		i++;
	}
	data->list = ft_sort(data->list);
}

void	create_list_32(t_data *data, size_t poids)
{
	uint32_t		i;

	i = 0;
	data->list = NULL;
	while (i < data->nsyms)
	{
		if ((void*)(data->symoff + i * sizeof(struct nlist)) > data->binary + data->size)
			return ;
		data->list = add_elem_end(data, data->list, (uint64_t)(data->symoff +
					i * sizeof(struct nlist)), poids);
		i++;
	}
	data->list = ft_sort(data->list);
}
