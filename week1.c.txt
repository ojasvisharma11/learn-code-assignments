#include <stdio.h>
#include<stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include<sys/wait.h>

pid_t ppid, cpid;

void child();
void parent();

//Write your code here
int get_child_exit_status()
{
    int status;
    waitpid(cpid, &status, 0);
    return WEXITSTATUS(status);  
        //Wait for the child to finish and get the status code.
}
int main(void)
{  
         
   ppid = getpid();
  
  
   //Write the code here to create a child process.
   cpid = fork();
    
   //inside the child process
   //-----------------------------------------------------------
    child();

   
  //-----------------------------------------------------------
  
  
   //inside the parent process
  //-----------------------------------------------------------

    printf("Child exited with status=%d",get_child_exit_status());
  //-----------------------------------------------------------
}

//DO NOT MODIFY CODE BELOW
void child()
{
        pid_t c_pid = getpid();
        if(c_pid == ppid)
        {
                // printf("This is not a child\n");
                return;
        }
        printf("This is a child\n");
        int status;
        scanf("%d",&status);
        exit(status);
}

