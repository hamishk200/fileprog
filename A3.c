#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define DB_NAME "userdb"
#define EXIT 4	
#define RESELECT 6

int createFile();
int getChoice();
void printMenu();
int fileExist(const char fileName[]);
int encrypt();
int encode();

int main(void)
{
	int userInput;
	int (*fun_ptr_arr[3])() = {createFile, encrypt, encode};
	while (userInput != EXIT)
	{
		printMenu();	
		userInput = getChoice();
		(*fun_ptr_arr[userInput])();
	}

	return 0;

}

void printMenu(void) {
	printf("\n"
		"1. Creat a file\n"
		"2. Encrypt\n"
		"3. anti- Encrypt\n"
		"4. load the flights from the database file\n"
		"5. exit the program\n"
		"Enter choice (number between 1-5)>\n");
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
		return 3;
		break;
	case 5:
		return EXIT;
		break;
	default:
		printf("Invalid choice\n");
		return RESELECT;
	}
}

int createFile()
{
	FILE* fp = NULL;
	char input[1000];
	printf("enter your diary:");
	fgets(input, 1000, stdin);
	char filename[20];
	printf("enter a file name:");
	scanf("%s", filename);
	fp = fopen(filename, "w");
	fprintf(fp, "%s", input);
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
	char filename[20], fileOutput[20];
	printf("Enter the file name you want to encrypt:\n");
	scanf("%s", filename);

	printf("Enter the out put file name:\n");
	scanf("%s", fileOutput);

	fp = fopen(filename, "r");
	fw = fopen(fileOutput, "w");

	if (fp == NULL)
	{
		printf("fp error\n");
		return 0;
	}
	if (fw == NULL)
	{
		printf("fw error\n");
		return 0;
	}
	else
	{
		while (!feof(fp))
		{
			char ch = fgetc(fp);
			ch = ch ^ 2;
			fputc(ch ,fw);
		}
	}
	fclose(fp);
	fclose(fw);
	return 0;
}

int encode()
{
	FILE* fp = NULL;
	FILE* fw = NULL;
	char filename[20], fileOutput[20];
	printf("Enter the file name you want to encode:\n");
	scanf("%s", filename);
	printf("Enter the out put file name:\n");
	scanf("%s", fileOutput);
	fp = fopen(filename, "r");
	fw = fopen(fileOutput, "w");
	if (fp == NULL || fw == NULL)
	{
		printf("fp error\n");
		return 0;
	}

	else
	{
		char str[1000];
		fgets(str, 1000, fp);
		int size = strlen(str);

		int i,k, j = 0;
		char count[50];
		int length;
		char dest[1000];
		for (i = 0; i < size; i++)
		{
			dest[j++] = str[i];
			length = 1;
			while (str[i] == str[i + 1])
			{
				length++;
				i++;
			}
			sprintf(count, "%d", length);
			for (k = 0; k < strlen(count); k++, j++)
			{
				dest[j] = count[k];
			}
		}
		dest[j] = '\0';
		printf("%s", dest);
		fprintf(fw, "%s", dest);
		fclose(fp);
		fclose(fw);
	}

	return 0;
}

