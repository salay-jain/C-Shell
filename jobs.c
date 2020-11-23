#include "headers.h"


void displayJobs(int numberOfProcess,int *childProcess,int *state)
{
	int i;
	for(i=0;i<numberOfProcess;i++)
	{
		if(childProcess[i]==-1)
			continue;
		char name[10];
		int pid,memSize,j,num;
		char* stats = (char*)malloc(256 * sizeof(char));
		sprintf(stats, "/proc/%d/stat", childProcess[i]);
		FILE * stat = fopen(stats, "r");
		if(stat==NULL)
		{
			printf("Error:PID does not exists\n");
			return;
		}
		fscanf(stat, "%d", &pid);
		fscanf(stat, "%s", name);
		fclose(stat);
		if(state[i]==1)
			printf("[%d] Running %s %d\n",i+1,name,childProcess[i]);
		else
			printf("[%d] Stopped %s %d\n",i+1,name,childProcess[i]);
	}
	return;
}