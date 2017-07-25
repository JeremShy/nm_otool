/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamhi <jcamhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/24 15:37:59 by jcamhi            #+#    #+#             */
/*   Updated: 2017/07/25 00:13:49 by jcamhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NM_H
# define NM_H

# ifdef __x86_64__
#  define CPUTYPE CPU_TYPE_X86_64
# endif
# ifdef __i386__
#  define CPUTYPE CPU_TYPE_I386
# endif

# include <stdio.h>
# include <ft_printf.h>
# include <libbinary.h>
# include <libft.h>
# include <ar.h>

typedef struct	s_symbole
{
	uint64_t			offset;
	void				*addr;
	char				*str;
	uint64_t			value;
	char				sym;
	int64_t				n_strx;
	int					is_debug;
	uint32_t			magic;
	size_t				poids;
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
	char		*sections;
	uint32_t	nbsect;
	uint32_t	end;
	off_t	size;
	const char	*av;
	int		endiancast;
	int		error;
}				t_data;

typedef struct	s_opt
{
	int	u;
	int	um;
}				t_opt;

void			find_boundaries_32(t_data *data, uint64_t offset);
void			find_boundaries_64(t_data *data, uint64_t offset);
void			find_boundaries_ppc(t_data *data, uint64_t offset);
void			handle_32(t_data *data, uint64_t offset, size_t poids);
void			handle_64(t_data *data, uint64_t offset, size_t poids);
void			handle_ppc(t_data *data, uint64_t offset, size_t poids);
void			create_list_64(t_data *data, size_t poids);
void			create_list_32(t_data *data, size_t poids);
t_symbole		*create_elem(t_data *data, uint64_t offset, size_t poids);
void			add_elem_start(t_data *data, t_symbole **list, uint64_t offset,
	size_t poids);
t_symbole		*add_elem_end(t_data *data, t_symbole *list, uint64_t offset,
	size_t poids);
void			print_list(t_data *data, t_symbole *list, t_opt opt);
void			delete_list(t_symbole *list);
t_symbole		*ft_sort(t_symbole *list);
void			handle_fat_cigam(t_data *data, t_opt opt);
void			handle_static_lib(t_data *data, uint32_t offset, t_opt opt);
int				ft_parsing(int ac, char **av, t_opt *opt);
int				find_start(int ac, char **av);
int64_t	get_good_endian(t_data data, int64_t nbr);
int	get_good_endianu(t_data data, uint64_t nbr);
// int	try_to_assign(void **ptr, void *value, t_data *data);

#endif
