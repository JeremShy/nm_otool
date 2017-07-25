/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fat_handle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamhi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/25 14:04:39 by jcamhi            #+#    #+#             */
/*   Updated: 2017/07/25 14:04:40 by jcamhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <nm.h>

int	fat_handle_32(t_data *data, struct fat_arch *arch, size_t poids, t_opt opt)
{
	if (ft_strnequ((char*)data->binary + arch->offset, ARMAG, SARMAG))
	{
		data->end = arch->offset + arch->size;
		if (data->end > (uint32_t)data->tend)
			return (0);
		handle_static_lib(data, arch->offset, opt);
	}
	else
		handle_32(data, arch->offset, poids);
	return (1);
}

int	fat_handle_64(t_data *data, struct fat_arch *arch, size_t poids, t_opt opt)
{
	if (ft_strnequ((char*)data->binary + arch->offset, ARMAG, SARMAG))
	{
		data->end = arch->offset + arch->size;
		if (data->end > (uint32_t)data->tend)
			return (0);
		handle_static_lib(data, arch->offset, opt);
	}
	else
		handle_64(data, arch->offset, poids);
	return (1);
}

int	fat_handle_ppc(t_data *data, struct fat_arch *arch, size_t poids, t_opt opt)
{
	data->endiancast = 1;
	if (ft_strnequ((char*)data->binary + arch->offset, ARMAG, SARMAG))
	{
		data->end = arch->offset + arch->size;
		if (data->end > (uint32_t)data->tend)
			return (0);
		handle_static_lib(data, arch->offset, opt);
	}
	else
		handle_32(data, arch->offset, poids);
	return (1);
}
