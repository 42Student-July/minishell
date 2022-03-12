#ifndef COMMON_H
# define COMMON_H

#include <stdio.h>
#include "libmem_mgt/mem_mgt.h"
// #include "libmem_mgt/replace_mem_mgt.h"

typedef enum e_stdio {
	STDIN = 0,
	STDOUT = 1,
	STDERR = 2
}						t_stdio;

extern int	g_exit_status;

#endif
