#include<stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{     

	FILE* filePointer;
	int wordExist=0;
	int bufferLength = 255;
	char search[100];
	printf("Enter word to be search=\n");
	scanf("\n%s",search);
	
	char cmpme[128];
	strncpy(cmpme," ",sizeof(" ")+1);
	strncat(cmpme,search,sizeof(search)+1);
	strncat(cmpme," ",sizeof(" ")+1);
	printf("\n%s\n",cmpme);

	
	char line[bufferLength];
	filePointer = fopen("file.txt", "r");
	while(fgets(line, bufferLength, filePointer))
	{
		char *ptr = strstr(line, cmpme);
		if (ptr != NULL) 
		{
			wordExist=1;
			break;
		}
	}
	fclose(filePointer);
	if (wordExist==1)
	{
		printf("Word exists.");
	}
	else 
	{
		printf("Word doesn't exist.");
	}
}
