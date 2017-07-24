/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libbinary.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamhi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/24 15:42:52 by jcamhi            #+#    #+#             */
/*   Updated: 2017/07/24 15:42:53 by jcamhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBBINARY_H
# define LIBBINARY_H

# include <sys/mman.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <unistd.h>
# include <stdio.h>
# include <stdio.h>
# include <mach-o/loader.h>
# include <mach-o/nlist.h>
# include <mach-o/stab.h>
# include <mach-o/fat.h>
# include <mach-o/ranlib.h>

char	*map_binary(const char *file);
int		unmap_binary(const char *file, void *addr);

#endif
