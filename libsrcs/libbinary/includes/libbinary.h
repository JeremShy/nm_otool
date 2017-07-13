#ifndef LIB_BINARY_H
# define LIB_BINARY_H

# include <sys/mman.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <unistd.h>
# include <stdio.h>

char	*map_binary(char *file);

#endif
