#include "mem_mgt.h"

/* 未解放メモリの情報を表示する関数 */
void	mem_mgt_check(const char *file, unsigned int line, const char *func)
{
	t_mem_info	*current;

	printf("\x1b[33m--------------leeks check--------------\x1b[39m\n");
	printf(" check place : %s:func %s:line %u\n", file, func, line);
	printf(" number      : %zu\n", g_mem_mgt.use_cnt);
	printf(" total size  : %zubyte\n", g_mem_mgt.use_byte);
	printf("\x1b[33m---------------------------------------\x1b[39m\n");
	current = g_mem_mgt.head;
	while (current != NULL)
	{
		printf(" address : %p\n", current->ptr);
		printf(" size    : %zubyte\n", current->size);
		printf(" place   : %s:func %s:line %u\n", current->file, \
				current->func, current->line);
		printf("\x1b[33m---------------------------------------\x1b[39m\n");
		current = current->next;
	}
}
