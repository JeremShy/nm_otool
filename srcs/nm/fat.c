/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamhi <jcamhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/24 15:35:52 by jcamhi            #+#    #+#             */
/*   Updated: 2017/07/25 13:19:40 by jcamhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <nm.h>

int	handle_fat_arch(t_data *data, struct fat_arch *arch, size_t poids,
	t_opt opt)
{
	if (data->binary + arch->offset > data->tend)
		return (0);
	data->magic = *(uint32_t*)(data->binary + arch->offset);
	if (arch->cputype == CPU_TYPE_I386)
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
	}
	else if (arch->cputype == CPU_TYPE_X86_64)
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
	}
	else if (arch->cputype == CPU_TYPE_POWERPC)
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
	}
	return (1);
}

void	print_head(cpu_type_t cputype, const char *filename)
{
	if (cputype == CPU_TYPE_I386)
		ft_printf("\n%s (for architecture i386):\n", filename);
	if (cputype == CPU_TYPE_X86_64)
		ft_printf("\n%s (for architecture X86_64):\n", filename);
	if (cputype == CPU_TYPE_POWERPC)
		ft_printf("\n%s (for architecture ppc):\n", filename);
}

void	print_all_arches(t_data *data, t_opt opt, size_t nbr)
{
	void	*data_cigam;
	struct fat_arch	*arch;
	size_t	i;

	if (data->binary + sizeof(struct fat_header) > data->tend)
	{
		data->error = 1;
		return ;
	}
	data_cigam = convert_chunk_alloc(data->binary + sizeof(struct fat_header),
			nbr * sizeof(struct fat_arch));
	i = 0;
	while (i < nbr)
	{
		arch = (struct fat_arch*)data_cigam + i;
		if ((void*)arch > data_cigam + data->size)
		{
			data->error = 1;
			return ;
		}
		if (arch->cputype == CPU_TYPE_I386 || arch->cputype == CPU_TYPE_X86_64 || arch->cputype == CPU_TYPE_POWERPC)
		{
			print_head(arch->cputype, data->av);
			data->endiancast = 0;
			handle_fat_arch(data, arch, i, opt);
			if (data->error)
				return ;
			print_list(data, data->list, opt);
			delete_list(data->list);
			data->list = NULL;
		}
		i++;
	}
	free(data_cigam);
}

void	handle_fat_cigam(t_data *data, t_opt opt)
{
	void				*data_cigam;
	struct fat_header	*header;
	struct fat_arch		*arch;
	size_t				i;
	size_t				nbr;

	data_cigam = convert_chunk_alloc(data->binary, sizeof(struct fat_header));
	header = (struct fat_header*)data_cigam;
	i = 0;
	nbr = header->nfat_arch;
	free(data_cigam);
	data_cigam = convert_chunk_alloc(data->binary + sizeof(struct fat_header),
			nbr * sizeof(struct fat_arch));
	while (i < nbr)
	{
		arch = (struct fat_arch*)data_cigam + i;
		if ((void*)arch > data_cigam + data->size)
		{
			data->error = 1;
			return ;
		}
		if (arch->cputype == CPUTYPE)
		{
			if (!handle_fat_arch(data, arch, i, opt))
				data->error = 1;
			free(data_cigam);
			return ;
		}
		i++;
	}
	print_all_arches(data, opt, nbr);
}
