#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE  100
#define TIMES  1000
#define random(x) (rand()%x)

int main()
{
	FILE *fp;
	if((fp=fopen("rand_num.ts","w"))==NULL)
	{
		printf("error in open file\n");
		exit(0);
	}
	int i,j;
	srand((int)time(0));
	for(i=0;i<TIMES;i++)
	{
		for (j=0;j<SIZE;j++)
		{
			//printf("%d\n",rand()%1000);
			int num=random(1000);
			printf("%d\n",num );
			if(fwrite(&num,sizeof(int),1,fp)!=1)
			{
				printf("error in write file\n");
				exit(1);
			}
		}

	}
	fclose(fp);
	return 0;
}