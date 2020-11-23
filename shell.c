#include "headers.h"

char *root,myhome[256];
int ln,ind,childProcess[10000],state[10000];
int noOfChildProcess = 0;
volatile sig_atomic_t signalis=0;

void sigintHandler() {
	printf(" Exiting Terminal............\n");
	exit(EXIT_FAILURE);
}


void bgProcessComplete()
{
	for (int i = 0; i < noOfChildProcess; i++)
	{
		int stat;
		pid_t wpid;
		wpid = waitpid(childProcess[i], &stat, WNOHANG);
		if (wpid != 0)
		{
			printf("Process with pid = %d exited normally\n", childProcess[i]);
			noOfChildProcess--;
			i--;
			for (int j = i + 1; j < noOfChildProcess; j++)
			{
				childProcess[j] = childProcess[j + 1];
				state[j]=state[j+1];
			}
			promptDisplay(0,myhome);	
			fflush(stdout);
		}
	}
	return;
}


void operateCommamd()
{
	char *command,*	commandTokens;
	signal(SIGINT,sigintHandler);
	signal(SIGCHLD, bgProcessComplete);
	while(1)
	{
		char* commandArgu[256];
		int position = 0;
		for(position=0;position<256;position++)
		{
			commandArgu[position]=NULL;
		}
		position = 0;

		promptDisplay(0,myhome);
		command=takeInput();

		commandTokens = strtok(command," \t\n");
		command = NULL;

		while(commandTokens!=NULL)
		{
			commandArgu[position]= commandTokens;
			position++;
			commandTokens = strtok(NULL, " \t\n");
		}

		commandTokens = NULL;
		commandArgu[position]=NULL;

		if(position==0)
			continue;

		if(commandArgu[position-1][0]!='&')
		{
			if(strcmp(commandArgu[0],"exit")==0)
				break;

			else if(strcmp(commandArgu[0],"pwd")==0)
			{
				printPWD(commandArgu);
			}
			else if(strcmp(commandArgu[0],"pinfo")==0)
			{
				printPinfo(commandArgu,position,myhome);
			}
			else if(strcmp(commandArgu[0],"echo")==0)
			{
				echoData(commandArgu,position);
			}
			else if(strcmp(commandArgu[0],"kill")==0)
			{
				for (int i = 0; i < noOfChildProcess; i++)
				{
					if(childProcess[i] == atoi(commandArgu[2]) && strcmp(commandArgu[1],"stop")==0)
					{
						kill(childProcess[i],SIGSTOP);
						state[i]=-1;
					}
					if(childProcess[i] == atoi(commandArgu[2]) && strcmp(commandArgu[1],"resume")==0)
					{
						kill(childProcess[i],SIGCONT);
						state[i]=1;
					}
				}

			}
			else if(strcmp(commandArgu[0],"ls")==0)
			{
				listFiles(commandArgu,position);
			}
			else if(strcmp(commandArgu[0],"cd")==0)				
			{
				changeDirectory(commandArgu,position,myhome);
			}
			else if(strcmp(commandArgu[0],"jobs")==0)				
			{
				displayJobs(noOfChildProcess,childProcess,state);
			}
			else
			{
				pid_t pid, wpid;
				int status;
				pid = fork();
				if (pid == 0)
				{
					if (execvp(commandArgu[0], commandArgu) == -1)
						perror("lsh");
					exit(EXIT_FAILURE);
				} 
				else if (pid < 0) 
				{
					perror("lsh");
				} 
				else 
				{
					do {
						wpid = waitpid(pid, &status, WUNTRACED);
					} while (!WIFEXITED(status) && !WIFSIGNALED(status));
				}
			}
		}
		else
		{
			commandArgu[position-1]=NULL;
			pid_t pid, wait_pid;
			pid = fork();
			if (pid < 0)
				perror("error");
			else if (pid == 0)
			{
				if (execvp(commandArgu[0], commandArgu) == -1)
					perror("error");
				exit(EXIT_FAILURE);
			}
			else
			{
				printf("Started process %d successfully\n", pid);
				childProcess[noOfChildProcess] = pid;
				state[noOfChildProcess] = 1;
				noOfChildProcess += 1;
			}

		}

	}
}

int main()
{
	char* currentDirectory=malloc(sizeof(char)*256);;
	getcwd(currentDirectory,256);
	printf("%s\n",currentDirectory);
	for(int i=0;i<strlen(currentDirectory);i++)
		myhome[i]=currentDirectory[i];
	free(currentDirectory);
	operateCommamd();
	return 0;
}