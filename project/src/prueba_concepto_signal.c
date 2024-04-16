#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

#define NUM_CHILD 4
#define SLEEP_CHILD 200
#define SLEEP_PARENT 1

void signal_parent(int signal)
{
    printf("SIGNAL recibido en el padre pero NO hago nada\n");
}

void signal_child(int signal)
{
    printf("SIGNAL recibido en un hijo por lo que salgo con exit failure\n");
    exit(EXIT_FAILURE);
}

void child()
{
    sleep(SLEEP_CHILD);
    exit(EXIT_SUCCESS);
}

void parent()
{
    int     i;
    pid_t   pid;
    int     status;

    signal(SIGINT, signal_parent);
    for (i =0;i< NUM_CHILD; i++)
    {
        pid = fork();
        if (pid != 0)
        {
            //padre
            if(pid < 0)
            {
                printf("ERROR al crear fork\n");
                exit(EXIT_FAILURE);
            }
            
        }
        else
        {
            signal(SIGINT, signal_child);
            //hijo
            child();
        }
    }
    sleep(SLEEP_PARENT);
    for (i = 0; i < NUM_CHILD; i++)
    {
        pid = wait(&status);
        printf("Fin de wait pid: %d  status: %d \n", pid, status);
    }
}

int main(void)
{
    printf("Init\n");
    parent();
    printf("Fin\n");
    return (EXIT_SUCCESS);
}