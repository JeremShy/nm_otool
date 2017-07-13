#include <nm.h>
#include <libbinary.h>

void	do_nm(char *file)
{
	char	*binary;

	binary = map_binary(file);
	if (!binary)
	{
		ft_printf("Error !!!\n");
	}
	else
		ft_printf("Pas d'erreur\n");
}

int		main(int ac, char **av)
{
	int		i;

	if (ac == 1)
		do_nm("a.out");
	else
	{
		i = 1;
		while(i < ac)
		{
			do_nm(av[i]);
			i++;
		}
	}
	return (0);
}
