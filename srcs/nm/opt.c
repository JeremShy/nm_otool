#include <nm.h>

static t_opt	ft_init(int *i)
{
	t_opt options;

	options.u = 0;
	options.um = 0;
	*i = 1;
	return (options);
}

int				find_start(int ac, char **av)
{
	int	i;
	int	cont;

	i = 1;
	cont = 1;
	while (i < ac && cont)
	{
		if (av[i][0] == '-')
			i++;
		else if (ft_strequ(av[i], "--"))
			return (i + 1);
		else
			return (i);
	}
	return (i);
}

void			check_validity(char *av)
{
	int	i;

	i = 1;
	while (av[i] != '\0')
	{
		if (av[i] != 'u' && av[i] != 'U')
		{
			ft_printf("nm: illegal option -- %c\n", av[i]);
			ft_printf("usage: nm [-uU] [file ...]\n");
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

void			norme_parsing(int i, char **av, t_opt *options)
{
	if (ft_strchr(av[i], 'u'))
		options->u = 1;
	if (ft_strchr(av[i], 'U'))
		options->um = 1;
}

t_opt			ft_parsing(int ac, char **av)
{
	t_opt	options;
	int		i;
	int		cont;

	options = ft_init(&i);
	cont = 1;
	while (i < ac && cont && !ft_strequ(av[i], "--"))
	{
		if (av[i][0] == '-')
		{
			check_validity(av[i]);
			norme_parsing(i, av, &options);
			i++;
		}
		else
			cont = 0;
	}
	return (options);
}
