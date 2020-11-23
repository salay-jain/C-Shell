#include "headers.h"

void operateLS(char *path,char *flag)
{
	//printf("%s\n",path);
	//printf("%s\n",flag);

	DIR *dir = opendir(path);

	if(dir == NULL)
	{
		printf("Error opening directory\n");
		return;
	}

	// Normal single line list if no flag or -a flag (show . & .. files also)
	if(strcmp(flag,"noflag")==0 || strcmp(flag,"-a")==0)
	{
		struct dirent *ent;	
		while((ent=readdir(dir))!=NULL)
		{	
			if((strcmp(ent->d_name,".")==0 || strcmp(ent->d_name,"..")==0 || ent->d_name[0]=='.' ) && strcmp(flag,"-a")!=0)
				continue;
			printf("%s ",ent->d_name);
		}
		printf("\n");
		closedir(dir);
	}
	// Create a list with relevant information as -l flag is present in argument
	else
	{
		//printf("%s\n",flag);

		struct dirent *ent;	
		while((ent=readdir(dir))!=NULL)
		{
			if((strcmp(ent->d_name,".")==0 || strcmp(ent->d_name,"..")==0 || ent->d_name[0]=='.' ) && strcmp(flag,"-l")==0)
				continue;
			struct stat st;
			stat(ent->d_name,&st);
			printf( (S_ISDIR(st.st_mode)) ? "d" : "-");
			printf( (st.st_mode & S_IRUSR) ? "r" : "-");
			printf( (st.st_mode & S_IWUSR) ? "w" : "-");
			printf( (st.st_mode & S_IXUSR) ? "x" : "-");
			printf( (st.st_mode & S_IRGRP) ? "r" : "-");
			printf( (st.st_mode & S_IWGRP) ? "w" : "-");
			printf( (st.st_mode & S_IXGRP) ? "x" : "-");
			printf( (st.st_mode & S_IROTH) ? "r" : "-");
			printf( (st.st_mode & S_IWOTH) ? "w" : "-");
			printf( (st.st_mode & S_IXOTH) ? "x" : "-");
			printf(" %2lu ", st.st_nlink);
			printf("  %s",getpwuid(st.st_uid)->pw_name); 
			printf("  %s",getgrgid(st.st_gid)->gr_name);
			printf(" \t%lld",(long long)st.st_size);	 	
			struct tm *timeinfo =localtime(&st.st_ctime);  
        	char timevalue[256];
        	strftime(timevalue, sizeof(timevalue), "%b %d %H:%M", timeinfo);
        	printf(" \t%s", timevalue);
			printf(" \t%s\n",ent->d_name);
		}
		printf("\n");
		closedir(dir);
	}
	return;
}

void listFiles(char **arg,int length)
{

	if(length==1)
	{
		operateLS(".","noflag");
	}
	else if(length==2)
	{
		if( strcmp(arg[1],"-a")==0 || strcmp(arg[1],"-l")==0 || strcmp(arg[1],"-al")==0 || strcmp(arg[1],"-la")==0 )
		{
			//printf("a");
			operateLS(".",arg[1]);
		}
		else
		{
			//printf("b");			
			operateLS(arg[1],"noflag");
		}
	}
	else if(length==3)
	{
		if( (strcmp(arg[1],"-a")==0 && strcmp(arg[2],"-l")==0) || (strcmp(arg[1],"-l")==0 && strcmp(arg[2],"-a")==0 ))
		{
			operateLS(".","-la");
		}
		else
		{
			operateLS(arg[2],arg[1]);
		}
	}
	else
	{
		operateLS(arg[3],"-la");
	}
	return;
}
