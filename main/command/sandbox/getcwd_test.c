#include "../includes/command.h"


#include<stdio.h>
#include<string.h>
#include<unistd.h>

#define PATHNAME_SIZE 512

int main(void)
{
	// 変数定義
	char pathname[PATHNAME_SIZE];  // ファイルパス

	// 変数初期化
	memset(pathname, '\0', PATHNAME_SIZE);

	// カレントディレクトリ取得
	getcwd(pathname, PATHNAME_SIZE);
	fprintf(stdout,"現在のファイルパス:%s\n", pathname);

	// カレントディレクトリ変更
	chdir("./test"); // チェンジディレクトリ
	getcwd(pathname, PATHNAME_SIZE);
	fprintf(stdout,"現在のファイルパス:%s\n", pathname);

	return 0;
}