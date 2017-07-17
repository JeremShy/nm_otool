#include <nm.h>

void		add_elem_start(t_data *data, t_symbole **list, uint64_t offset)
{
	t_symbole	*elem;

	elem = create_elem(data, offset);
	*list = elem;
}

t_symbole		*add_elem_end(t_data *data, t_symbole *list, uint64_t offset)
{
	t_symbole *elem;
	t_symbole	*fl;

	if (!(elem = create_elem(data, offset)))
		return (NULL);
	if (!list)
		return (elem);
	fl = list;
	while (list->next != NULL)
		list = list->next;
	list->next = elem;
	return (fl);
}

void	print_list(t_data *data, t_symbole *list)
{
	while(list)
	{
		if (!list->is_debug)
		{
			if (list->value)
				ft_printf("%016llx ", list->value);
			else
				ft_printf("%16c ", ' ');
			ft_printf("%c ", list->sym);
	 		ft_printf("%s\n", list->str);
		}
		list = list->next;
	}
	data = NULL;
}
