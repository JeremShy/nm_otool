/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_binary.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamhi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/24 15:41:45 by jcamhi            #+#    #+#             */
/*   Updated: 2017/07/24 15:42:22 by jcamhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libbinary.h>

char	*map_binary(const char *file)
{
	char		*ret;
	int			fd;
	struct stat	buf;

	if ((fd = open(file, O_RDONLY)) < 0)
		return (NULL);
	if (fstat(fd, &buf) < 0)
	{
		close(fd);
		return (NULL);
	}
	if ((ret = mmap(0, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0))
			== MAP_FAILED)
	{
		close(fd);
		return (NULL);
	}
	close(fd);
	return (ret);
}
