#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char* argv[])
{
    int pid = fork();
    if (pid < 0)
    {
        perror("fork failed");
        return 1;
    }
    if (pid == 0)
    {
        // child process
        printf("child process pid=%d\n", getpid());

        // execute ls
        char* args[] = { "/bin/ls", "-l", NULL };
        execv(args[0], args);

        // should not reach here unless execv fails
        perror("execv failed");
        exit(1);
    }
    else
    {
        // parent process
        printf("parent process pid=%d, child pid= %d, waiting for child...\n", getpid(), pid);
        wait(NULL);
        printf("parent process exiting\n");
    }
    return 0;
}