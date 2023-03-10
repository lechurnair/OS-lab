#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/wait.h>
#include<stdbool.h>
#include <sys/types.h>
#include <fcntl.h>
#include <signal.h>

//struct sigaction express what to do when the given signal is received. 
//The structure consists of a handler, a mask, and some flags
struct sigaction SIG_Child;
struct sigaction SIG_Int;
//declared pid as a global variable
pid_t pid;
//If SIGINT is called then then to check and print new prompt line
bool SIGINT_check;
//To prevent zombification of  process. Sometimes, child process terminates but wait is not called
//Kernel will hold on to their status until parent calls wait
//WNOHANG prevents wait()/waitpid() from blocking so that your process can go on with other tasks. 
//If a child died, its pid will be returned by wait()/waitpid() and your process can act on that else returns 0
void SIGCHLD_Handler()
{
	while (waitpid(-1, NULL, WNOHANG) > 0) {
	}
	printf("\n");
}

//Kill the current process and again print the shell prompt
//Checker to prevent printing of prompt twice
void SIGINT_Handler(int p){
	if (kill(pid,SIGTERM) == 0)
	{
		printf("\nSIGINT signal received\n");	
		SIGINT_check = true;
	}else{
		printf("\n");
	}
}

//Ctrl+Z signal handler
//suspends current process
void SIGTSTP_Handler(int p)
{
	if(pid>0)
		printf("\nSIGSTP Received and Handled\n");
}

// Touch function created file if not present in directory
// before performing I/O redirection processes
void Touch(char *fp_name, bool background)
{
	char *cmd[] = {"touch",fp_name, NULL};
	pid = fork();
	if(pid == 0)
	{
		execvp(cmd[0], cmd);
	}
	else if(pid > 0)
	{
		if(background) {}
		else { wait(0); }
		
	}
	else
	{
		fprintf(stderr, "fork failed.\n");
	}
}

//Pipehandler for command pipelines processes
void Pipehandler(char * args[], bool background)
{
	//initialising 2 pipes, one for input and another for output
	//[0] --> output, [1] --> input of the pipe
	int Pipe1[2];
	int Pipe2[2];
	pipe(Pipe1);
	pipe(Pipe2);
	bool file_handler = false, pipe_swich = false;
	int num_args = 1, file_hand, filepointer;
	
	char *command[50];
	
	int j = 0, k = 0;
	
	//finding number of processes between pipes
	while (args[k] != NULL){
		if (strcmp(args[k],"||") == 0){
			num_args++;
		}
		k++;
	}
	
	for(int i = 0; i < num_args; i++)
	{
		//storing one process in command array
		k = 0;
		while (strcmp(args[j],"||") != 0){
			command[k] = args[j];
			j++;	
			k++;
			if (args[j] == NULL){
				//cheching, is I/O redirection processes
				//are present in processes
				if(strcmp(args[j-2], ">>>") == 0)
				{
					file_handler = true;
					file_hand = 1;
					
				}
				else if(strcmp(args[j-2], "&>>") == 0)
				{
					file_handler = true;
					file_hand = 2;
					
				}
				break;
			}
		}
		j++;
		command[k] = NULL;
		
		pid=fork();
		
		if(pid == -1){			
			printf("Child process could not be created\n");
			break;
		}
		if(pid == 0)
		{
			//replacing the stdin and stdout with pipe
			//in such a way that output of one process
			//is input of next process by the help of
			//pipe_swich boolea variable
			//if pipe_swich is TRUE and pipe1 is storing output
			//then in next process pipe_swich is FALSE and we taking input from pipe1
			if (i == 0) { dup2(Pipe1[1], 1); }
			else if (i == num_args - 1)
			{
				if (pipe_swich){ dup2(Pipe1[0], 0); }
				else { dup2(Pipe2[0], 0); }
				
				if(file_handler)
				{
					//if Output redirection processes
					//are present in processes
					//then performing it
					if(file_hand == 1)
					{
						Touch(command[k-1], background);
						filepointer = open(command[k-1], O_WRONLY);
						dup2(filepointer, 1);
					}
					else if(file_hand == 2)
					{
						Touch(command[k-1], background);
						filepointer = open(command[k-1], O_WRONLY);
						dup2(filepointer, 2);
					}
					command[k-1] = NULL;
					command[k-2] = NULL;
				}
			}
			else
			{
				if (pipe_swich)
				{
					dup2(Pipe1[0], 0); 
					dup2(Pipe2[1], 1);
				}
				else
				{
					dup2(Pipe2[0], 0); 
					dup2(Pipe1[1], 1);					
				} 
			}
			
			execvp(command[0],command);//calling exec() system call
		}
		
		//closing the file pointer		
		if (i == 0){ close(Pipe1[1]); }
		else if (i == num_args - 1)
		{
			if (pipe_swich){ close(Pipe1[0]); }
			else{ close(Pipe2[0]); }
		}
		else
		{
			if (pipe_swich)
			{					
				close(Pipe1[0]);
				close(Pipe2[1]);
			}
			else
			{					
				close(Pipe2[0]);
				close(Pipe1[1]);
			}
		}
		
		//waiting for the child process to finish or background mode
		if(background) { printf("%d\n", pid); }
		else { wait(0); }
		
		//changing the value of pipe_swich
		pipe_swich = !pipe_swich;	
	}
}

//filehandler for I/O redirection processes
void filehandler(char *arg[], int x, bool background)
{
	int i = 0;
	int filepointer;
	
	pid = fork();
	if(pid == 0)
	{
		if(x == 0)
		{
			while(strcmp(arg[i], "<<<") != 0) i++;//finding the file name
			filepointer = open(arg[i+1], O_RDONLY);//initialising file pointer corresponding to file name
			dup2(filepointer, 0);//replacing the stdin with file pointer
		}
		else if(x == 1)
		{
			while(strcmp(arg[i], ">>>") != 0) i++;//finding the file name
			Touch(arg[i+1], background);//creating file if not present in directory
			filepointer = open(arg[i+1], O_WRONLY);//initialising file pointer corresponding to file name
			dup2(filepointer, 1);//replacing the stdout with file pointer
		}
		else if(x == 2)
		{
			while(strcmp(arg[i], "&>>") != 0) i++;//finding the file name
			Touch(arg[i+1], background);//creating file if not present in directory
			filepointer = open(arg[i+1], O_WRONLY);//initialising file pointer corresponding to file name
			dup2(filepointer, 2);//replacing the stderr with file pointer
		}
		arg[i] = NULL;
		arg[i+1] = NULL;
		execvp(arg[0], arg);//calling exec() system call
	}
	else if(pid > 0)
	{
		//waiting for the child process to finish or background mode
		if(background) { printf("%d\n", pid); }
		else { wait(0); }
		
	}
	else
	{
		fprintf(stderr, "fork failed.\n");
	}
}

int main()
{
	//we call the method of initialization and the welcome screen
	system("clear");
	printf("******************************************"); 
	printf("\n\n   ****112001019_112001037's SHELL****"); 
	printf("\n\n******************************************"); 
	printf("\n");
	//signal handlers associated with the structure
	SIG_Child.sa_handler = SIGCHLD_Handler;
	SIG_Int.sa_handler = SIGINT_Handler;
	sigaction(SIGCHLD, &SIG_Child, 0);
	sigaction(SIGINT, &SIG_Int, 0);
	//Signal and its handler function
	signal(SIGTSTP, SIGTSTP_Handler);
	int x;
	SIGINT_check = false;
	char Input[500];
	char xp[500];
	while(1)
	{
		bool background = false;
		for(int i = 0; i < 500; i++)
		{
			Input[i]='\0';
		}
		char* argu[50];
		//To prevent double printing
		if(!SIGINT_check)
		write(1, ">>>  ", 5);//printing Shell Prompt
		SIGINT_check = false;
		
		fgets(Input, 500, stdin);//taking input
		strcpy(xp, Input);//storing input in xp
		
		//checking wheather process will run in background or not
		if(strstr(Input, "&\n")){ background = true; }
		else if(strstr(Input, "& ")){ background = true; }
		
		//breaking input in arguments and storing it in argu array
		char* c = " \t\r\n\a";
		argu[0] = strtok(Input, c);
		for(int i = 1; i < 50; i++)
		{
			argu[i] = strtok(NULL, c);
		}
		
		//performing process corresponding to input 
		if (argu[0] == NULL) {}
		else if(strcmp(argu[0], "cd") == 0)//performing process corresponding to Change Directory
		{
			if (argu[1] == NULL)//if directory not given
			{
				fprintf(stderr, "directory not given\n");
			}
			else
			{
				if (chdir(argu[1]) != 0)//changing directory
				{
					fprintf(stderr, "No such directory exist\n");
				}
			}
		}
		else if(strcmp(argu[0], "pwd") == 0)//performing process corresponding to finding Print Working Directory
		{
			char ptr[50];
			for(int i = 0; i < 50; i++)
			{
				ptr[i]='\0';
			}
			getcwd(ptr, 50);//getting current working directory
			write(1, ptr, 50);//printing current working directory
			write(1, "\n", 1);
		}
		else if(strcmp(argu[0], "exit") == 0)//performing process corresponding to Exit
		{
			exit(0);//Exit
		}
		
		else if(strstr(xp, "||"))//performing process corresponding to pipes
		{
			Pipehandler(argu, background);
		}
		//performing process corresponding to I/O redirection
		else if(strstr(xp, "<<<"))
		{
			filehandler(argu, 0, background);
		}
		else if(strstr(xp, ">>>"))
		{
			filehandler(argu, 1, background);
		}
		else if(strstr(xp, "&>>"))
		{
			filehandler(argu, 2, background);
		}
		//or other processes corresponding to executable
		//present in system
		else
		{
			pid = fork();
			if(pid == 0)
			{
				//calling exec() system call
				execvp(argu[0], argu);
			}
			else if(pid > 0)
			{
				//waiting for the child process to finish or background mode
				if(background) { printf("%d\n", pid); }
				else { wait(0); }
				
			}
			else
			{
				fprintf(stderr, "fork failed.\n");
			}
		}
	}
	return 0;
}
