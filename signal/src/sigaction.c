
#include "sigaction.h"

// デバッグ用の関数
void	print_exit_status_in_signal()
{
	if (g_exit_status == 0)
		printf("%d ", g_exit_status);
	else
		printf("%d ", g_exit_status);
}

