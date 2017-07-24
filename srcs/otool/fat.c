#include <otool.h>

void		*convert_chunk(void *binary, size_t size)
{
	char		*ret;
	char		*bc;
	char		*tmp;
	size_t		i;

	ret = (char*)malloc(size);
	bc = (char*)binary;
	tmp = ret;
	i = 0;
	while (i < size)
	{
		*(tmp + 0) = *(bc + 3);
		*(tmp + 1) = *(bc + 2);
		*(tmp + 2) = *(bc + 1);
		*(tmp + 3) = *(bc + 0);
		tmp += 4;
		bc += 4;
		i += 4;
	}
	return (ret);
}

static void	handle_fat_arch_32(t_data *data, struct fat_arch *arch)
{
	if (ft_strnequ((char*)data->binary + arch->offset, ARMAG, SARMAG))
	{
		data->end = arch->offset + arch->size;
		ft_printf("Archive : %s\n", data->av);
		handle_static_lib(data, arch->offset);
	}
	else
	{
		ft_printf("%s:\n", data->av);
		handle_32(data, arch->offset);
	}
}

void		handle_fat_arch(t_data *data, struct fat_arch *arch)
{
	data->magic = *(uint32_t*)(data->binary + arch->offset);
	if (arch->cputype == CPU_TYPE_I386)
	{
		handle_fat_arch_32(data, arch);
	}
	else if (arch->cputype == CPU_TYPE_X86_64)
	{
		if (ft_strnequ((char*)data->binary + arch->offset, ARMAG, SARMAG))
		{
			data->end = arch->offset + arch->size;
			ft_printf("Archive : %s\n", data->av);
			handle_static_lib(data, arch->offset);
		}
		else
		{
			ft_printf("%s:\n", data->av);
			handle_64(data, arch->offset);
		}
	}
}

void		handle_fat(t_data *data)
{
	void				*data_cigam;
	struct fat_header	*header;
	struct fat_arch		*arch;
	size_t				i;
	size_t				nbr;

	data_cigam = convert_chunk(data->binary, sizeof(struct fat_header));
	header = (struct fat_header*)data_cigam;
	i = 0;
	nbr = header->nfat_arch;
	free(data_cigam);
	data_cigam = convert_chunk(data->binary + sizeof(struct fat_header),
			nbr * sizeof(struct fat_arch));
	while (i < nbr)
	{
		arch = (struct fat_arch*)data_cigam + i;
		if (arch->cputype == CPUTYPE)
		{
			handle_fat_arch(data, arch);
			free(data_cigam);
			return ;
		}
		i++;
	}
}
