/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unmap_binary.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamhi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/24 15:42:03 by jcamhi            #+#    #+#             */
/*   Updated: 2017/07/24 15:42:10 by jcamhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libbinary.h>

int	unmap_binary(const char *file, void *addr)
{
	int			fd;
	struct stat	buf;

	if ((fd = open(file, O_RDONLY)) < 0)
		return (-1);
	if (fstat(fd, &buf) < 0)
	{
		close(fd);
		return (-1);
	}
	if (munmap(addr, buf.st_size) == -1)
	{
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}
