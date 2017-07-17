#include <nm.h>

char	get_char_for_symtype(struct nlist_64 elem, t_data data, t_symbole *ret)
{
	if ((elem.n_type & N_STAB) != 0)
	{
		ret->is_debug = 1;
	}
	else if ((elem.n_type & N_TYPE) == N_UNDF)
		return ('U');
	else if ((elem.n_type & N_TYPE) == N_ABS)
		return ('A');
	else if ((elem.n_type & N_TYPE) == N_SECT)
	{
		if (elem.n_sect >= data.sect_text_beg && elem.n_sect <= data.sect_text_end)
			return ('T');
		if (elem.n_sect >= data.sect_data_beg && elem.n_sect < data.sect_data_end)
			return ('D');
		if (elem.n_sect >= data.sect_bss_beg && elem.n_sect <= data.sect_bss_end)
			return ('B');
		return ('S');
	}
	return ('X');
}

t_symbole	*init_symbole_for_64(t_data *data, uint64_t offset, t_symbole *ret)
{
	struct nlist_64 *nl;
	char	*strings;

	strings = (char*)(data->binary + data->stroff);
	nl = (struct nlist_64*)(data->binary + offset);
	if ((ret->n_strx = (int64_t)nl->n_un.n_strx) != 0)
	{
		ret->str = ft_strdup(strings + ret->n_strx);
		// ft_printf("Creating elem with string : %s\n", ret->str);
	}
	else
		ret->str = NULL;
	ret->value = nl->n_value;
	ret->is_debug = 0;
	ret->sym = get_char_for_symtype(*nl, *data, ret);
	return (ret);
}

t_symbole	*create_elem(t_data *data, uint64_t offset)
{
	t_symbole	*ret;

	// ft_printf("calling create_elem with offset %lx\n", offset);
	ret = (t_symbole*)malloc(sizeof(t_symbole));
	ret->next = NULL;
	ret->addr = data->binary + offset;
	ret->offset = offset;
	if (data->magic == MH_MAGIC_64)
	{
		ret = init_symbole_for_64(data, offset, ret);
	}
	return (ret);
}
