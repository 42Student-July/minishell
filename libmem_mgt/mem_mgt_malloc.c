#include "mem_mgt.h"

/* メモリ確保とそのメモリの情報を記録する関数 */
void	*mem_mgt_malloc(size_t size, const char *file, unsigned int line,
		const char *func)
{
	t_mem_info	*new;
	t_mem_info	*current;
	t_mem_info	*prev;

	if (g_mem_mgt.use_byte + size > MAX_SIZE)
	{
		printf("The maximum size that can be allocated by malloc has been exceeded.\n");
		mem_mgt_free_all();
		exit(1);
	}
	new = (t_mem_info *)malloc(sizeof(t_mem_info));
	if (new == NULL)
		return (NULL);
	new->ptr = malloc(size);
	if (new->ptr == NULL)
	{
		free(new);
		return (NULL);
	}
	g_mem_mgt.use_byte += size;
	g_mem_mgt.use_cnt++;
	new->mem_mgt_ptr = (void *)new;
	new->size = size;
	new->file = file;
	new->line = line;
	new->func = func;
	new->next = NULL;
	if (g_mem_mgt.head == NULL)
	{
		g_mem_mgt.head = new;
		return (new->ptr);
	}
	current = g_mem_mgt.head;
	while (current != NULL)
	{
		prev = current;
		current = current->next;
	}
	prev->next = new;
	current = new;
	return (new->ptr);
}
