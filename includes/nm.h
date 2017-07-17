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
	char			sym;
	int64_t		n_strx;
	int				is_debug;
	struct s_symbole	*next;
}				t_symbole;

typedef struct	s_data
{
	void		*binary;
	t_symbole	*list;
	uint32_t	magic;
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
	uint32_t	stroff;
	uint32_t	strsize;
	uint32_t	symoff;
	uint32_t	nsyms;
}				t_data;

void				find_boundaries_64(t_data *data);
t_symbole		*create_elem(t_data *data, uint64_t offset);
void				add_elem_start(t_data *data, t_symbole **list, uint64_t offset);
t_symbole		*add_elem_end(t_data *data, t_symbole *list, uint64_t offset);
void				print_list(t_data *data, t_symbole *list);
t_symbole		*ft_sort(t_symbole *list);

#endif
