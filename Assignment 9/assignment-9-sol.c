#include<stdio.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<string.h> 
#include<sys/wait.h> 
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include<sys/msg.h>
void child();
void parent();  
int get_child_exit_status();
int msgid;
int commands=0;

typedef struct command_type
{
    long type;
    //The command to execute
    char command[32];
    //The arguments for the command
    int args[2];
} command_t;
typedef struct result_type 
{
    long type;
    int result;
} result_t;

//WRITE YOUR CODE HERE
//Create a message queue and return the message queue id
int create_message_queue()
{
    key_t key = ftok("msgQueue", 65);
    int msgid = msgget(key, 0666 | IPC_CREAT);
    printf("msgid = %d\n", msgid);
    return msgid;
}


//send a command via message queue
//msgid - ID of the Message queue
int send_command(int msgid, command_t cmd)
{
    int operatorStatus = msgsnd(msgid, &cmd.command, sizeof(cmd.command), 0);
    int operand1Status = msgsnd(msgid, &cmd.args[0], sizeof(cmd.args[0]), 0);
    int operand2Status = msgsnd(msgid, &cmd.args[1], sizeof(cmd.args[1]), 0);
    int cmdStatus = msgsnd(msgid, &cmd, sizeof(cmd), 0);
    printf("%d \n", cmdStatus);
    if(operatorStatus>=0 && operand1Status>=0 && operand2Status>=0){
        return 0;
    }
    return -1;
}
//Read the command from the message queue
//msgid - ID of the Message queue
command_t *recv_command(int msgid)
{
    int message;
    msgrcv(msgid, &message, sizeof(message), 1, 0);
    printf("%d", message);
    return NULL;
}

//Send the result via message queue
//msgid - ID of the Message queue
int send_result(int msgid, result_t result)
{
    return 0;
}
//Read the Result from the message queue
//msgid - ID of the Message queue
result_t *recv_result(int msgid)
{
    return NULL;
}
//Delete the message queue
void delete_message_queue(int msgid)
{
    msgctl(msgid, IPC_RMID, NULL);
}
void parent(){

    for(int i=1;i<=commands;i++)    
    {
        command_t *cmd = (command_t*) malloc(sizeof(command_t));;
        result_t *result;
        char operator[32];
        scanf("%s", operator);
        printf("%s ", operator);
        int operand1, operand2;
        scanf("%d", &operand1);
        printf("%d ", operand1);
        scanf("%d", &operand2);
        printf("%d\n", operand2);
        strcpy(cmd->command, operator);
        cmd->args[0] = operand1;
        cmd->args[1] = operand2;
        int status = send_command(msgid, *cmd);
        printf("Return of send_message %d\n", status);
          //WRITE CODE HERE TO READ THE COMMAND FROM INPUT
      
        //SEND THE COMMAND via send_command
          
        //RECIEVE THE RESULT from CHILD
      
        // printf("CMD=%s, RES = %d\n",cmd->command,result->result);
        
    }
    printf("Child exited with status:%d\n",get_child_exit_status());
    delete_message_queue(msgid);

}
void child()
{
    for(int i=1;i<=commands;i++)    
    {
        command_t *cmd;
        //WRITE CODE to RECIEVE THE COMMAND,use recv_command method.
        // cmd = recv_command(msgid);
          //WRITE CODE to process the command.
      
        //SEND RESULT via send_result
      
    }

        exit(commands); 
}

//DO NOT MODIFY CODE BELOW
int main(int argc, char* argv[]) 
{ 
    pid_t cid; 
    msgid = create_message_queue(); 
    scanf("%d",&commands);
    if(msgid <= 0 )
    {
        printf("Message Queue creation failed\n");
    }
    cid = fork(); 

    // Parent process 
    if (cid == 0) 
    { 
        child();
    } else if(cid > 0 )
    {
        parent();
    }
} 

//Get the exit code of the child.
int get_child_exit_status()
{
        int stat;
        wait(&stat);
        return WEXITSTATUS(stat);
}
