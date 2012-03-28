#include <stdio.h>
#include <stdlib.h>

void swap(int *a,int *b)
{
	int temp;
	temp=*a;
	*a=*b;
	*b=temp;
}
/*
void quick_sort(int i,int j,int *a)
{
	int mid = a[(i+j)/2];
	int l=i,r=j;
	if(i<j)
{
	while(l<r)
	{
		while(a[l]<mid&&l<r) l++;
		while(a[r]>mid&&l<r) r--;
		if(l<r)
		swap(&a[l],&a[r]);
	    if (a[l]==a[r])
	    	l++;
	}

	quick_sort(i,r-1,a);
	quick_sort(l,j,a);
}
}*/
void quick_sort(int s[],int l,int r)
{
	int i,j,x;
	if(l<r)
	{
		i=l;
		j=r;
		x=s[i];
		while(i<j)
			 
		{
			while(i<j&&s[j]>x) j--;
			if(i<j) s[i++]=s[j];
			while(i<j&&s[i]<x) i++;
			if(i<j) s[j--]=s[i];
		}
		s[i]=x;
		quick_sort(s,l,i-1);
		quick_sort(s,i+1,r);

	}
}

int main(int argc, char const *argv[])
{
	/* code */
/*	
	int a[7]={9,9,10,9,9,9,9};
	quick_sort(0,6,a);
	int i;
	for(i=0;i<7;i++)
	{
		printf("%d\n",a[i]);
	}
		*/
	int i,j;
	FILE *fp;
	FILE *tp;
    if((fp=fopen("rand_num.ts","r"))==NULL)
    {
    	printf("error in open file\n");
    	exit(1);
    }
    if((tp=fopen("other.ts","w"))==NULL)
    {
    	printf("error in open file\n");
    	exit(1);
    }


    int a[100];
    for (i=0;i<1000;i++)
   {
    	if(fread(a,sizeof(int),100,fp)!=100)
    	{
    		printf("error in read file\n");
    	}
    	quick_sort(a,0,99);
    	for (j=0;j<100;j++)
    	{
    		printf("%d ",a[j]);
            if(fwrite(&a[j],sizeof(int),1,tp)!=1)
            {
            	printf("error int while \n");
            }	
    	}
    	printf("\n");
    	
    }

    fclose(fp);
    fclose(tp);
	return 0;
}