#ifndef MEM_MGT_H
# define MEM_MGT_H

# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>

/* 確保できるサイズの上限(byte) */
# define MAX_SIZE 100000

/* メモリ管理構造体 */
typedef struct s_mem_info
{
	void				*ptr;
	size_t				size;
	const char			*file;
	unsigned int		line;
	const char			*func;
	void				*mem_mgt_ptr;
	struct s_mem_info	*next;
}	t_mem_info;

typedef struct s_mem_mgt
{
	t_mem_info	*head;
	size_t		use_byte;
	size_t		use_cnt;
}	t_mem_mgt;

/* メモリ情報を格納する構造体 */
t_mem_mgt	g_mem_mgt;

/* 関数のプロトタイプ宣言 */

void	*mem_mgt_malloc(size_t size, const char *file, unsigned int line, const char *func);
void	mem_mgt_free(void *ptr);
void	mem_mgt_finish_check(int n);
void	mem_mgt_check(const char *file, unsigned int line, const char *func);
void	mem_mgt_free_all();

#endif
