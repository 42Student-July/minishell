#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <stdbool.h>
#include "../includes/command.h"

int main(int argc, char const *argv[])
{
	(void)argc;
	char	**split_array;
	
	// 二次元配列がNULLになることはない。
	// equalがある時と無い時ではarray[1]にどちらもNULLが入ってしまう。
	// そのせいで=が入っているかどうか判定できない。
	// → 嘘 引数が ""だった場合、NULLが入るように実装されている
	// separatorが文字列中に存在しない場合、最初の配列にすべての文字が入る
	split_array = ft_split(argv[1], '=');
	printf("split_array = %p\n", split_array[0]);
	printf("split_array = %s\n", split_array[0]);
	printf("split_array = %s\n", split_array[1]);
	return 0;
}
