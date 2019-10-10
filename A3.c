#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h> 

#define EXIT 4	
#define RESELECT 6

int createFile();
int getChoice();
void printMenu();
int fileExist(const char fileName[]);
int encrypt();
int showAll();
int search();

int main(void)
{
	int userInput;
	/*function pointer*/
	int (*fun_ptr_arr[4])() = {createFile, encrypt, showAll, search};
	/*if the user input is not equal to EXIT, the function will loop*/
	while (userInput != EXIT)
	{
		printMenu();	
		userInput = getChoice();
		if(userInput != EXIT && userInput <= 3 && userInput >= 0)
		{
			(*fun_ptr_arr[userInput])();
		}
		
	}
	return 0;
}

void printMenu(void) 
{
	printf("\n"
		"1. Creat a file\n"
		"2. Encrypt\n"
		"3. anti- Encrypt\n"
		"4. Show all available books\n"
		"5. Search\n"
		"6. Exit\n"
		"Enter choice (number between 1-6)>\n");
}

int getChoice()
{
	int input;
	printf("Input your choice\n");
	scanf("%d", &input);
	while ((getchar()) != '\n');
	switch (input) 
	{
	case 1:
		return 0;
		break;
	case 2:
		return 1;
		break;
	case 3:
		return 1;
		break;
	case 4:
		return 2;
		break;
	case 5:
		return 3;
		break;
	case 6:
	    return 4;
	    break;
	default:
		printf("Invalid choice\n");
		return RESELECT;
	}
}

int createFile()
{
	FILE* fp = NULL;
	char input[1000];/*store the diary from the user*/
	printf("enter your diary:");
	fgets(input, 1000, stdin);
	char filename[20];
	printf("enter a file name:");
	scanf("%s", filename);
	fp = fopen(filename, "w");/*write the name to the file*/
	fprintf(fp, "%s", input);/*write the context to the file*/
	fclose(fp);
	return 0;
}

int fileExist(const char fileName[])
{
	FILE* fpSource;
	fpSource = fopen(fileName, "r");
	if (fpSource == NULL)
	{
		printf("Your targe file not exist\n");
		return 0;
	}
	return 1;
}


int encrypt()
{
	FILE* fp = NULL;
	FILE* fw;
	/*fliename use to read the file will be encrypt, 
	fileOutout use to write the encrypt context*/
	char filename[20], fileOutput[20];
	printf("Enter the file name you want to encrypt:\n");
	scanf("%s", filename);

	printf("Enter the out put file name:\n");
	scanf("%s", fileOutput);

	fp = fopen(filename, "r");
	fw = fopen(fileOutput, "w");

	if (fp == NULL)
	{
		printf("Your target file not exist\n");
		return 0;
	}

	else
	{
		while (!feof(fp))/*read the context of the target file*/
		{
			char ch = fgetc(fp);/*get each characters from the file*/
			ch = ch ^ 2;/*encrypt*/
			fputc(ch ,fw);/*put the encrypt context into the new file*/
		}
	}
	fclose(fp);
	fclose(fw);
	return 0;
}

int showAll()
{
	DIR *d;
    struct dirent *dir;
 	d = opendir(".");
	if (d) 
	{
		while ((dir = readdir(d)) != NULL)
		{
			printf("%s\n", dir->d_name);
		}
		closedir(d);
	}
	return 0;
}

int search()
{
	char keyworld[20];
	printf("Enter your key world\n");
	scanf("%s", keyworld);
	FILE* fp = NULL;
	fp = fopen(keyworld, "r");
	if(fp == NULL)
	{
		printf("The book you searched is not exits\n");
	}
	else
	{
		printf("The book you want is: %s\n", keyworld);
	}
	return 0;
}
