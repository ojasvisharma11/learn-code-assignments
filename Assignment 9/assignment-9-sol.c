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
    return msgid;
}


//send a command via message queue
//msgid - ID of the Message queue
int send_command(int msgid, command_t cmd)
{
    cmd.type = 1;
    int cmdStatus = msgsnd(msgid, &cmd, sizeof(cmd), 0);
    return cmdStatus;
}
//Read the command from the message queue
//msgid - ID of the Message queue
command_t *recv_command(int msgid)
{
    command_t *cmd = (command_t*) malloc(sizeof(command_t));
    msgrcv(msgid, &cmd, sizeof(cmd), 1, 0);
    return cmd;
}

//Send the result via message queue
//msgid - ID of the Message queue
int send_result(int msgid, result_t result)
{
    result.type = 2;
    int resultStatus = msgsnd(msgid, &result, sizeof(result_t), 0);
    return resultStatus;
}
//Read the Result from the message queue
//msgid - ID of the Message queue
result_t *recv_result(int msgid)
{
    result_t *result = (result_t*) malloc(sizeof(result_t));
    msgrcv(msgid, &result, sizeof(result), 2, 0);
    return result;
}
//Delete the message queue
void delete_message_queue(int msgid)
{
    msgctl(msgid, IPC_RMID, NULL);
}

int add(int operand1, int operand2){
    return operand1 + operand2;
}

int sub(int operand1, int operand2){
    return operand1 - operand2;
}

int mul(int operand1, int operand2){
    return operand1 * operand2;
}

result_t *calculateResult(command_t cmd){
    result_t *result = (result_t*) malloc(sizeof(result_t));
    if(cmd.command[0] == 'A'){
        result->result = add(cmd.args[0], cmd.args[1]);
    }
    else if(cmd.command[0] == 'S'){
        result->result = sub(cmd.args[0], cmd.args[1]);
    }
    else if(cmd.command[0] == 'M'){
        result->result = mul(cmd.args[0], cmd.args[1]);
    }
    return result;
}
void parent(){

    for(int i=1;i<=commands;i++)    
    {
        command_t *cmd = (command_t*) malloc(sizeof(command_t));
        scanf("%s%d%d", cmd->command, &cmd->args[0], &cmd->args[1]);
        
        int status = send_command(msgid, *cmd);
        result_t *result = recv_result(msgid);
        printf("CMD=%s, RES = %d\n",cmd->command,result->result);
        
    }
    printf("Child exited with status:%d\n",get_child_exit_status());
    delete_message_queue(msgid);

}
void child()
{
    for(int i=1;i<=commands;i++)    
    {
        command_t *cmd;
        cmd = recv_command(msgid);
        
        result_t *result = calculateResult(*cmd);
        
        int status = send_result(msgid, *result);
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
