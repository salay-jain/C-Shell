#include "headers.h"

void promptDisplay(int lewn,char *myh)
{
	char *usr,*path,cwd[256],*base,*loc;
	usr=getenv("USER");
	printf("<%s:",usr);
	getcwd(cwd,sizeof(cwd));
	printf("%s> ",cwd);
}
