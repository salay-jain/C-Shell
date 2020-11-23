#include "headers.h"

void changeDirectory(char **arg,int length,char *myhome)
{
	if(length==1)
	{
		chdir(myhome);
	}
	else
	{
		if(arg[1][0]=='~')
		{
			char tempLocation[256]="";
			int len1= strlen(myhome);
			int len2 = strlen(arg[1]);
			for(int i = 0;i<len1;i++)
				tempLocation[i]=myhome[i];
			for(int i = 1;i<len2;i++)
				tempLocation[len1+i-1]=arg[1][i];
			arg[1]=tempLocation;
			printf("s %s\n",arg[1]);
		}
		int check = chdir(arg[1]);
		if(check==-1)
			printf("Directory does not exist.\n");
	}
	return;
}