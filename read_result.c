#include <stdio.h>
#include <stdlib.h>

int main(int argc,char *argv[])
{
	FILE *fp;
	if((fp=fopen(argv[1],"r"))==NULL)
	{
		printf("error in open file %s\n",argv[1]);
		exit(0);
	}
	int num=0;
	int id[1000];
	char attribute[1000][50];
	while(fread(&id[num],sizeof(int),1,fp)!=0)
	{
	    if(fread(attribute[num],sizeof(char),50,fp)!=50)
	    {
	    	printf("error in read attribute\n");
	    	exit(0);
	    }
	     num++;	
	}
	int i;
	for (i=0;i<num;i++)
	{
		printf("%d %s\n",id[i],attribute[i]);
	}
	fclose(fp);
	return 0;
}