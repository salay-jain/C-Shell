#include "headers.h"

void printPinfo(char **arg,int length,char* myhome)
{
	int pid;
	if(arg[1]!=NULL)
	{
		pid = atoi(arg[1]);
		if(kill(pid,0)==-1)
		{
			printf("Invalid PID\n");
			return;
		}

	}
	else
	{
		pid = getpid();
	}
	char* stats = (char*)malloc(256 * sizeof(char));
	char* memoryFile = (char*)malloc(256 * sizeof(char));
	char* linkname = (char*)malloc(256 * sizeof(char));    
	char name[10],status,buf1[256],buf2[256];
	int memorySize,lastIndex,i=0,j=1;

	sprintf(stats, "/proc/%d/stat", pid);
	FILE* stat = fopen(stats, "r");
	fscanf(stat, "%d", &pid);
	fscanf(stat, "%s", name);
	fscanf(stat, " %c", &status);
	fclose(stat);
	free(stats);

	sprintf(memoryFile, "/proc/%d/statm", pid);
	FILE* memory = fopen(memoryFile, "r");
	fscanf(memory, "%d", &memorySize);
	fclose(memory);
	free(memoryFile);

	sprintf(linkname, "/proc/%d/exe", pid);
	lastIndex = readlink(linkname, buf1, 256);
	buf1[lastIndex] = 0;

	if(strstr(buf1,myhome) !=NULL)
	{
		for(i=0;i<strlen(myhome);i++)
		{
			if(buf1[i] != myhome[i])
				break;
		}
		buf2[0]='~';
		while(buf1[i]!='\0')
			buf2[j++] = buf1[i++];
		strcpy(buf1,buf2);
	}
	printf("pid -- %d\n", pid);
	printf("Process Status -- %c\n", status);
	printf("memory -- %d\n", memorySize);
	printf("Executable Path -- %s\n", buf1);
	return;
}