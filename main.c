/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *    Description:  词法分析器主程序
 *        Created:  2012年03月13日 12时46分49秒
 *       Compiler:  gcc
 *         Author:  cloudaice (), 
 *
 * =====================================================================================
 */
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define  BUFFER_SIZE  100
#define  WORD_SIZE    100

struct id_attribute
{
      int id;
      char attribute[50];
};
typedef struct id_attribute token;

static char Buffer[BUFFER_SIZE];
static unsigned  int  state=0;
static unsigned  int  lexeme_pointer=0;
static unsigned  int  word_pointer=0;
static char str_buffer[WORD_SIZE];
static token all_word[1000];
unsigned  int  error_row=0;
FILE* fp;
FILE* tp;

void fail();
token gettoken(int id,int buffer_back);
token nexttoken();
char nextchar();
void load_buffer();
char get_char();
void back_word_buffer();

int main(int argc, char* argv[])
{
      if((!argv[1])||(!argv[2]))
      {
            printf("no source filename or target file\n");
            return 0;
      }
      int word_count=0;
      int i;
      if((fp=fopen(argv[1],"r"))==NULL)
      {
            printf("error in open file %s\n",argv[1]);
            exit(0);
      }
      load_buffer();
      while(get_char()!=EOF)
      {
            printf("lexeme_pointer %d\n",lexeme_pointer);
            token temp_token = nexttoken();
            if(temp_token.id!=0)
            {
            all_word[word_count++]=temp_token;
            }

      }
      for (i=0;i<word_count;i++)
      {
            printf("%d %s\n",all_word[i].id,all_word[i].attribute);
      }
      printf("want to write into file %s y\\n\n",argv[2]);
      char result=getchar();
      if(result!='y')
            return 0;
      if((tp=fopen(argv[2],"w"))==NULL)
      {
            printf("error in open file %s\n",argv[2]);
            exit(0);
      }
      for (i=0;i<word_count;i++)
      {
           if(fwrite(&all_word[i].id,sizeof(int),1,tp)!=1)
           {
            printf("error in write id\n");
            exit(0);
           } 
           if(fwrite(all_word[i].attribute,sizeof(char),50,tp)!=50)
           {
            printf("error in write attribute\n");
            exit(0);
           }
      }
      fclose(tp);
      fclose(fp);
return 0;
}

void load_buffer()
{
      int num;
      if((num=fread(Buffer,sizeof(char),BUFFER_SIZE,fp))<0)
      {
            printf("error in load buffer\n");
            exit(1);
      }
      printf("num %d\n",num);
      if(feof(fp)!=0)
      {
            Buffer[num]=EOF;
      } 
}
char get_char()
{
      if(lexeme_pointer==BUFFER_SIZE)
      {
            load_buffer(fp);
            lexeme_pointer=0;
      }
      return Buffer[lexeme_pointer];
}

char nextchar()
{
      if(lexeme_pointer==BUFFER_SIZE)
      {
            load_buffer(fp);
            lexeme_pointer=0;
      }
      str_buffer[word_pointer++]=Buffer[lexeme_pointer++];
      str_buffer[word_pointer]='\0';
      if(str_buffer[word_pointer-1]=='\n')
            error_row++;
      return str_buffer[word_pointer-1];
}

void back_word_buffer()
{
      word_pointer--;
      str_buffer[word_pointer]='\0';
}
token gettoken(int id,int buffer_back)
{
      int i;
      if(buffer_back)
      {
            word_pointer--;
            str_buffer[word_pointer]='\0';
            lexeme_pointer--;
      }
      token temp_token;
      temp_token.id=id;
      for(i=0;str_buffer[i]!='\0';i++)
      {
            temp_token.attribute[i]=str_buffer[i];
      }
      temp_token.attribute[i]=str_buffer[i];
      word_pointer=0;
      str_buffer[word_pointer]='\0';
      return temp_token;
}
void  fail()
{
      printf("in %d:   ",error_row);
      printf("there is something error around %s\n",str_buffer);
      exit(1);
}
/* token function */
token nexttoken()
{
    char c;
    state=0;
    while(1)
    {
        switch(state)
        {
            case 0:
            c = nextchar();
            if(c==EOF) 
            {
                  return gettoken(0,1);
            }
            else if((c==' ')||(c=='\n')||(c=='\t'))
            {
                back_word_buffer();
                state=0;
            }
            else if((c==';')||(c=='=')) state=1;
            else if((c=='+') || (c=='-') || (c=='*') ) state=2;
            else if(isdigit(c)) state=3;
            else if(c=='/') state=8;
            else if(c=='i') state=11;
            else if(c=='d') state=15;
            else if(isalpha(c)) state=22;
            else state=24;
            break;

            case 1:
            return gettoken(1,0);//fen ge fu ; =
            break;

            case 2:
            return gettoken(2,0);// yun suan fu + - * /

            case 3:
            c=nextchar();
            if(isdigit(c)) state=3;
            else if (c=='.') state=4;
            else state=7;
            break;

            case 4:
            c=nextchar();
            if(isdigit(c)) state=5;
            else state=24;// error state
            break;

            case 5:
            c=nextchar();
            if(isdigit(c)) state=5;
            else state=6;
            break;

            case 6:
            return gettoken(3,1); //double digit

            case 7:
            return gettoken(4,1);//int digit

            case 8:
            c=nextchar();
            if(c=='/') state=9;
            else state=25;
            break;

            case 9:
            c=nextchar();
            if(c=='\n') state=10;
            else if(c==EOF) state=26;
            else state=9;
            break;

            case 10:
            return gettoken(5,1); //zhu shi 

            case 11:
            c=nextchar();
            if(c=='n') state=12;
            else state=22;
            break;

            case 12:
            c=nextchar();
            if(c=='t') state=13;
            else state=22;
            break;

            case 13:
            c=nextchar();
            if(c==' ') state=14;
            else state=22;
            break;

            case 14:
            return gettoken(6,1);//key word

            case 15:
            c= nextchar();
            if(c=='o') state=16;
            else state=22;
            break;

            case 16:
            c=nextchar();
            if(c=='u') state=17;
            else state=22;
            break;

            case 17:
            c= nextchar();
            if(c=='b') state=18;
            else state=22;
            break;

            case 18:
            c= nextchar();
            if(c=='l') state=19;
            else state=22;
            break;

            case 19:
            c=nextchar();
            if(c=='e') state=20;
            else state=22;
            break;

            case 20:
            c = nextchar();
            if(c==' ') state=21;
            else state=22;
            break;

            case 21:
            return gettoken(6,1);

            case 22:
            c=nextchar();
            if(isalpha(c)||isdigit(c)) state=22;
            else state=23;
            break;

            case 23:
            return gettoken(7,1);

            case 24:
            printf("syntax error:\n");
            fail();           //error function 

            case 25:
            return gettoken(2,1);

            case 26:
            return gettoken(5,1);

            default: state=24;

        }
    }
}