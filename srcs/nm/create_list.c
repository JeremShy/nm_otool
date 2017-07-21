#include <nm.h>

void	create_list_64(t_data *data, size_t poids)
{
	struct nlist_64	*array;
	uint32_t		i;

	array = (struct nlist_64*)((void*)(data->binary) + data->symoff);
	i = 0;
	data->list = NULL;
	while (i < data->nsyms)
	{
		data->list = add_elem_end(data, data->list, (uint64_t)(data->symoff +
					i * sizeof(struct nlist_64)), poids);
		i++;
	}
	data->list = ft_sort(data->list);
}

void	create_list_32(t_data *data, size_t poids)
{
	struct nlist	*array;
	uint32_t		i;

	array = (struct nlist*)((void*)(data->binary) + data->symoff);
	i = 0;
	data->list = NULL;
	while (i < data->nsyms)
	{
		data->list = add_elem_end(data, data->list, (uint64_t)(data->symoff +
					i * sizeof(struct nlist)), poids);
		i++;
	}
	data->list = ft_sort(data->list);
}
