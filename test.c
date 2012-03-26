#include <stdio.h>
#include <string.h>
static char buffer[100];
int main()
{
    char *s;
    s=buffer;
    s[1]='e';
    printf ("%c\n",buffer[1]);
    char c;
    c=getchar();
    while(c!=EOF)
    {
        if (c=='\n')
        {
            printf("换行\n");
            break;
        }
        else if (c=='\t')
        {
            printf("tab\n");
        }
        else if (c==' ')
        {
            printf("空格\n");
        }
        else
        {
            printf("%c\n",c);
        }
        c=getchar();
    }
}
