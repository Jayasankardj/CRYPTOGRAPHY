#include<stdio.h>
#include<string.h>

int main()
{
	char alpha[]={'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
	char mono[]={'f','k','l','m','n','g','h','i','j','a','b','c','d','e','o','u','v','w','x','y','z','p','q','r','s','t'};
	char pt[100],ct[100]="";
	int i;
	printf("\nEnter Plain Text: ");
	scanf("%s",pt);
	char *ptr=pt;
	while(*ptr !='\0')
	{
		char ch=*ptr;
		for(i=0;i<26;i++)
		{
			if(ch==alpha[i])
			{
				strncat(ct,&mono[i],1);
			}
		}
		ptr++;
	}
	printf("\nCipher Text: %s\n",ct);
	
	return 0;
}
