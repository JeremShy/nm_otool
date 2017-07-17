#ifndef NM_H
# define NM_H

# include <stdio.h>
# include <ft_printf.h>
# include <libbinary.h>

typedef struct	s_data
{
	void	*binary;
	uint64_t	begin_text;
	uint64_t	end_text;
	uint64_t	begin_data;
	uint64_t	end_data;
}				t_data;

void	find_text_data_boundaries_64(t_data *data);

#endif
