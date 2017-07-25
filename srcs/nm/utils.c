#include <nm.h>

int64_t	get_good_endian(t_data data, int64_t nbr)
{
	if (data.endiancast)
		return (convert_chunk(&nbr));
	return (nbr);
}

int	get_good_endianu(t_data data, uint64_t nbr)
{
	if (data.endiancast)
		return (convert_chunk_u(&nbr));
	return (nbr);
}

int	try_to_assign(void **ptr, void *value, t_data *data)
{
	if (value <= data->binary + data->size)
	{
		if (ptr)
			*ptr = value;
		return (1);
	}
	data->error = 1;
	return (0);
}
