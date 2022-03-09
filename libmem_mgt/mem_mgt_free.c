#include "mem_mgt.h"

/* メモリの解放とそのアドレスのメモリ情報を記録から削除する関数 */
void	mem_mgt_free(void *ptr)
{
	t_mem_info	*prev;
	t_mem_info	*current;

	if (g_mem_mgt.head == NULL)
	{
		free(ptr);
		return ;
	}
	current = g_mem_mgt.head;
	if (current->ptr == ptr)
	{
		g_mem_mgt.head = current->next;
		g_mem_mgt.use_byte -= current->size;
		g_mem_mgt.use_cnt--;
		free(current->mem_mgt_ptr);
		free(ptr);
		return ;
	}
	while (current != NULL)
	{
		if (current->ptr == ptr)
		{
			prev->next = current->next;
			g_mem_mgt.use_byte -= current->size;
			g_mem_mgt.use_cnt--;
			current->ptr = NULL;
			current->size = 0;
			current->file = NULL;
			current->line = 0;
			current->func = NULL;
			free(current->mem_mgt_ptr);
			current->mem_mgt_ptr = NULL;
			break ;
		}
		prev = current;
		current = current->next;
	}
	free(ptr);
}
