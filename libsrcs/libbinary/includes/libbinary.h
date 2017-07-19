#ifndef LIB_BINARY_H
# define LIB_BINARY_H

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

char	*map_binary(const char *file);

#endif
