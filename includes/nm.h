#ifndef NM_H
# define NM_H

# include <stdio.h>
# include <ft_printf.h>
# include <libbinary.h>
# include <libft.h>

typedef struct	s_symbole
{
	uint64_t			offset;
	void				*addr;
	char				*str;
	uint64_t			value;
	char			sym;
	int64_t		n_strx;
	int				is_debug;
	uint32_t	magic;
	size_t		poids;
	struct s_symbole	*next;
}				t_symbole;

typedef struct	s_data
{
	void		*binary;
	t_symbole	*list;
	uint32_t	magic;
	uint32_t	stroff;
	uint32_t	strsize;
	uint32_t	symoff;
	uint32_t	nsyms;
	char			*sections;
}				t_data;

void				find_boundaries_64(t_data *data, uint64_t offset);
void				find_boundaries_32(t_data *data, uint64_t offset);
void				handle_32(t_data *data, uint64_t offset, size_t poids);
void				handle_64(t_data *data, uint64_t offset, size_t poids);
void				create_list_64(t_data *data, size_t poids);
void				create_list_32(t_data *data, size_t poids);
t_symbole		*create_elem(t_data *data, uint64_t offset, size_t poids);
void				add_elem_start(t_data *data, t_symbole **list, uint64_t offset, size_t poids);
t_symbole		*add_elem_end(t_data *data, t_symbole *list, uint64_t offset, size_t poids);
void				print_list(t_data *data, t_symbole *list);
t_symbole		*ft_sort(t_symbole *list);
void				handle_fat_cigam(t_data *data);

#endif
