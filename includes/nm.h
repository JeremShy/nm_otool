#ifndef NM_H
# define NM_H

# include <stdio.h>
# include <ft_printf.h>
# include <libbinary.h>

typedef struct	s_symbole
{
	uint64_t			offset;
	void				*addr;
	char				*str;
	uint64_t			value;
	struct s_symbole	*next;
}				t_symbole;

typedef struct	s_data
{
	void		*binary;
	t_symbole	*list;
	uint64_t	begin_text;
	uint64_t	end_text;
	uint32_t	sect_text_beg;
	uint32_t	sect_text_end;
	uint64_t	begin_data;
	uint64_t	end_data;
	uint32_t	sect_data_beg;
	uint32_t	sect_data_end;
	uint64_t	begin_bss;
	uint64_t	end_bss;
	uint32_t	sect_bss_beg;
	uint32_t	sect_bss_end;
}				t_data;

void			find_boundaries_64(t_data *data);
t_symbole	*create_elem(t_data *data, uint64_t offset);

#endif
