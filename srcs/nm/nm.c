#include <nm.h>
#include <libbinary.h>

int main(int ac, char **av)
{
	if (ac != 2)
		return (1);
	char *binary = map_binary(av[1]);
	if (!binary)
	{
		ft_printf("Error !!!\n");
		return (1);
	}
	else
		ft_printf("Pas d'erreur\n");
	return (0);
}
