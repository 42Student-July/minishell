#ifndef REPLACE_MEM_MGT_H
# define REPLACE_MEM_MGT_H

# define malloc(s) mem_mgt_malloc(s, __FILE__, __LINE__, __FUNCTION__)
# define free(ptr) mem_mgt_free(ptr)
# define exit(n) mem_mgt_finish_check(n)
# define mem_mgt_check() mem_mgt_check(__FILE__, __LINE__, __FUNCTION__)

#endif
