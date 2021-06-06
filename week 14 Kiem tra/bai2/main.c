#include "avl.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int isSplitPoint(char c)
{
	if(c==' ' || c=='.'|| c==','|| c=='!'
		|| c=='?'|| c==':'|| c==';'|| c=='('|| c==')')
		return 1;
	return 0;
}
int main()
{
	
	node *root=NULL;
	char x[20];
	
	root = loadDict();
	
	// load doan van dau vao
	char input[1000];
	printf("Van ban can check:\n");
	fflush(stdin);
	gets(input);
	char checkWord[20];
	
	// tach tu va check
	int i=0,k, count=0;
	while( i<strlen(input))
	{
		int j=i+1;
		while(j<strlen(input) && isSplitPoint(input[j])==0)
			j++;
		if(j>=strlen(input)) j = strlen(input)-1;
		if(j>i)
		{
			for(k=0; k<j-i; k++)
				checkWord[k] = input[k+i];
			checkWord[k] = '\0';
			
			//printf("|%s|\n",checkWord);
			/*
			1. loai bo ky tu cach trong o dau moi tu neu co
			2. check xem tu do co ky tu HOA hay khong, neu co
			thi khong can check trong tu dien
			*/
			Jval newWord;
			newWord.s = checkWord;
			if(containKey(root,newWord)==0)
			{
				count++;
				printf("tu sai:%s\n",checkWord);
			}
		}
		i=j+1;
		while(i<strlen(input) && isSplitPoint(input[i])==1)i++;
	}
	if(count==0)
		printf("Van ban vua nhap hoan toan dung chinh ta\n"); 	
	return 0;
}
