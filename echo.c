#include "headers.h"

void echoData(char **arg, int length)
{
	//printf("%d\n", length);
	for(int i=1;i<length;i++)
		printf("%s ",arg[i]);
	printf("\n");
	return;
}