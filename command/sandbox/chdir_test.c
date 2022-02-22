#include<stdio.h>
#include<string.h>
#include<unistd.h>

static void	print_cwd(void)
{
    char pathname[1024] = {"\0"};
    getcwd(pathname, 1024);
    printf("%s\n", pathname);
}

int	main(void)
{
    int rc = 0;
    int fd = 0;
    rc = chdir("/virtual/..");
    if(rc < 0){
		printf("error\n");
    }
    print_cwd();

    // rc = chdir("..");
    // if(rc < 0){
    //     printf("Error: chdir(%d) %s\n", errno, strerror(errno));
    //     return(-1);
    // }
    // print_cwd();

    // rc = chdir("./minishell_command");
    // if(rc < 0){
    //     printf("Error: chdir(%d) %s\n", errno, strerror(errno));
    //     return(-1);
    // }
    // print_cwd();

    // fd = open("/etc", O_RDONLY);
    // if(fd < 0){
    //     printf("Error: open(%d) %s\n", errno, strerror(errno));
    //     return(-1);
    // }
    // rc = fchdir(fd);
    // if(rc < 0){
    //     printf("Error: fchdir(%d) %s\n", errno, strerror(errno));
    //     return(-1);
    // }
    // print_cwd();

    return(0);
}
