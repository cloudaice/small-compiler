#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 100

static char buffer[BUFFER_SIZE];

unsigned int pointer =0;

void load_buffer( FILE *fp)
{
	int num;
	if((num=fread(buffer,sizeof(char),100,fp))<0)
	{
		printf("error in load buffer\n");
		exit(1);
	}
	printf("num %d\n",num);
	if(feof(fp)!=0)
	{
		buffer[num]=EOF;
		printf("yes\n");
	}
}
int  main(int argc, char const *argv[])
{
	if(!argv[1])
	{
		printf("no file\n");
		return 0;
	}
	FILE *fp;
	if((fp=fopen(argv[1],"r"))==NULL)
	{
		printf("error in open file %s\n",argv[1]);
	}
	load_buffer(fp);
	int i=0;
	while(buffer[pointer]!=EOF)
	{
		printf("%d %c\n",i++,buffer[pointer]);
		pointer++;
		if (pointer==100)
		{
			load_buffer(fp);
			pointer=0;
		}
	}
	fclose(fp);
	return 0;
}