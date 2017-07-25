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

void	set_error_and_return(t_data *data)
{
	data->error = 1;
	return ;
}
