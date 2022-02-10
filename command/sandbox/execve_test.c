#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>
#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
	pid_t pid;
	extern char **environ;

	/* 複数子プロセスの終了を待つ場合など、
		fork() 処理中は SIGCHLD をブロックする*/

	pid = fork();
	if (pid > 0) {
	/* 親プロセス */
	write(1, "parent process\n", 15);
	} else if (pid == 0) {
	/* 子プロセス */
	write(1, "child process\n", 14);

	/* 意図しない fd の複製によるバグを防ぐ */
	/* 0=stdin, 1=stdout, 2=stderr */
	/* 1024= ulimit -n の結果 */
	int i;
	for(i = 3; i < 1024; i++) {
		close(i);
	}

	argv[0] = "echo";
	argv[1] = "Hello World!";
	argv[2] = NULL;

	execve("/bin/echo", argv, environ);
	perror("execve");                    /* ここに到達した場合はエラー */
	_exit(0);
	} else {
	/* エラー */
	perror("fork");
	}

	return 0;
}