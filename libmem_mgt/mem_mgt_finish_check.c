#include "mem_mgt.h"

/* 未解放メモリの情報を表示し、全て解放し、プログラムを終了する関数 */
void	mem_mgt_finish_check(int n)
{
	t_mem_info	*current;

	if (g_mem_mgt.use_cnt == 0)
		exit(0);
	printf("\x1b[31m--------Detect memory leaks!!!!--------\x1b[39m\n");
	printf(" number     : %zu\n", g_mem_mgt.use_cnt);
	printf(" total size : %zubyte\n", g_mem_mgt.use_byte);
	printf("\x1b[31m---------------------------------------\x1b[39m\n");
	current = g_mem_mgt.head;
	while (current != NULL)
	{
		printf(" address : %p\n", current->ptr);
		printf(" size    : %zubyte\n", current->size);
		printf(" place   : %s:func %s:line %u\n", current->file, \
				current->func, current->line);
		printf("\x1b[31m---------------------------------------\x1b[39m\n");
		current = current->next;
	}
	mem_mgt_free_all();
	exit(n);
}
