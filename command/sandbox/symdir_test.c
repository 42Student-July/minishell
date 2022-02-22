/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symdir_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhirabay <mhirabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 10:13:04 by mhirabay          #+#    #+#             */
/*   Updated: 2022/02/21 23:48:31 by mhirabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>

#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

static void	print_cwd(void)
{
    char pathname[1024] = {"\0"};
    getcwd(pathname, 1024);
    printf("%s\n", pathname);
}

int main() {
	char fn[]="test.file";
	char sln[]="piyo";
	int fd;
	FILE *fp;
	struct dirent *dirst;
	struct stat buf;
	struct stat buf_2;

	mkdir("hoge", 0755);
	mkdir("hoge/huga", 0755);
	print_cwd();
	symlink("hoge", sln);
	// chdirをコメントアウトすると、S_ISLNKが1になる
	chdir("piyo/huga");
	print_cwd();
	lstat(sln, &buf);
	printf("link = %d\n", S_ISLNK(buf.st_mode));
	remove("hoge");
	remove("piyo");
//   if ((fd = creat(fn, S_IWUSR)) < 0)
//     perror("creat() error");
//   else {
//     close(fd);
//     puts("before symlink()");
//     system("ls -il test.*");
	
    // if (!= 0) {
//       perror("symlink() error");
//       unlink(fn);
//     }
//     else {
// 		lstat(sln, &buf);
// 		lstat(fn, &buf_2);
// 		// printf("link = %d\n", buf_2.st_nlink);
// 		printf("link = %d\n", S_ISLNK(buf_2.st_mode));
// 		// printf("link = %d\n", buf.st_nlink);
// 		printf("link = %d\n", S_ISLNK(buf.st_mode));
//     //   puts("after symlink()");
//     //   system("ls -il test.*");
//     //   unlink(fn);
//     //   puts("after first unlink()");
//     //   system("ls -il test.*");
//     //   unlink(sln);
//     }
// 		remove("test.file");
// 		remove("test.symlink");
//   }
}

// int main()
// {
// 	FILE *fp;
// 	struct dirent *dirst;
// 	struct stat buf;

// 	mkdir("test_dir_01", 0755);
// 	printf("stat()実行 : %d\n\n", stat("test_dir_01", &buf));
// 	printf("ディレクトリ[test_dir_01]に関する情報\n");
// 	printf("    st_mode : %#o\n", buf.st_mode);
// 	printf("    st_uid  : %ld\n", (long)buf.st_uid);
// 	printf("    st_gid  : %ld\n", (long)buf.st_gid);
// 	printf("    st_size : %ld\n", (long)buf.st_size);
// 	printf("    st_atimespec(秒) : %ld\n", (long)buf.st_atimespec.tv_sec);
// 	printf("    st_mtimespec(秒) : %ld\n", (long)buf.st_mtimespec.tv_sec);
// 	printf("    st_ctimespec(秒) : %ld\n\n", (long)buf.st_ctimespec.tv_sec);

// 	fp = fopen("test_dir_01/test_file_01.txt", "w");
// 	fclose(fp);

// 	remove("test_dir_01/test_file_01.txt");
// 	remove("test_dir_01");

// 	return 0;
// }
