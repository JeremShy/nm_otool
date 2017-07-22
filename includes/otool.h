#ifndef OTOOL_H
# define OTOOL_H

# include <stdio.h>
# include <ft_printf.h>
# include <stdio.h>
# include <ft_printf.h>
# include <libbinary.h>
# include <libft.h>
# include <ar.h>

typedef struct	s_data
{
	void		*binary;
	uint32_t	magic;
	uint32_t	stroff;
	uint32_t	strsize;
	uint32_t	symoff;
	uint32_t	nsyms;
	char		*sections;
	uint32_t	nbsect;
	uint32_t	end;
	const char	*av;
}				t_data;

void	handle_64(t_data *data, uint64_t offset);
void	handle_32(t_data *data, uint64_t offset);
void	print(t_data *data, void *start, uint64_t size, uint64_t print_size);

#endif
