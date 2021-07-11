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
	return 0;
}


//send a command via message queue
//msgid - ID of the Message queue
int send_command(int msgid, command_t cmd)
{
	return 0;
}
//Read the command from the message queue
//msgid - ID of the Message queue
command_t *recv_command(int msgid)
{
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
	
}
void parent(){

	for(int i=1;i<=commands;i++)	
	{
		command_t *cmd;
      	result_t *result;
      	//WRITE CODE HERE TO READ THE COMMAND FROM INPUT
      
		//SEND THE COMMAND via send_command
      	
        //RECIEVE THE RESULT from CHILD
      
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
        //WRITE CODE to RECIEVE THE COMMAND,use recv_command method.
      
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
