#include "mem_mgt.h"

/* 未解放メモリを解放する関数 */
void	mem_mgt_free_all()
{
	t_mem_info	*current;

	current = g_mem_mgt.head;
	while (current != NULL)
	{
		if (current->ptr != NULL)
			mem_mgt_free(current->ptr);
		current = current->next;
	}
}
