#include <stdio.h>
#include <string.h>
#include <stdlib.h>
struct person
{
	int age;
	int height;
	int* sex;
	/* data */
};
/*
struct person lucy;
lucy.age=18;
lucy.height=170;
lucy->sex=1;
*/


	int a=10;
typedef struct person people;
people fun(people * lucy)
{
	(*lucy).age=19;
	(*lucy).height=170;
	lucy->sex=&a;
	return (*lucy);
}

static char buffer[10];
int main(int argc, char const *argv[])
{
	/* code */
	FILE* fp;
	if((fp=fopen("lexeme.lex","r"))==NULL)
	{
		printf("some error in open this file\n");
		exit(1);
	}

    char *c;
    char *s;
    s=buffer;
    int i;
    int count=0;
    while((c=fgets(s,10,fp))!=NULL)
    {
    	count++;
    	for (i=0;buffer[i]!='\0';i++)
    	{
    		if(buffer[i]!=EOF)
    		{
    			printf("%d %c\n",i,buffer[i]);
    //			printf("%c",buffer[i] );
    		}
    	}
    }
    people lucy;
    people tom=fun(&lucy);
    printf("\ncount %d\n", count);
    printf("%d %d\n", tom.age,*tom.sex);
	return 0;
}