//////////////////////////////////////////Roni Polisanov 307835884 Amit Shwartz 305432775//////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "m_darray.h"
#include "m_student.h"

int main(int argc, char * argv[])
{
	int i, capacity = 10, FLAG = 1, index=0;
	char choice, name[N_SIZE], id[T_SIZE];
	DA da;
	ST temp;
	//input.txt argument
	FILE* fp = fopen(argv[1], "r");
	if (fp == NULL)
		printf("Erorr fopen\n");

	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	system("COLOR 8E");
	printf("Last seen in the system: %d/%d/%d %d:%d:%d\n",tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);

	//maximum number of students
	printf("Enter the maximum number of students that are will be in the system: ");
	scanf("%d", &capacity);
	//create dynamic array pointer
	da = create_dArray(capacity);
	//reading from argv[1] (input.txt)
	read_from_file(fp, da);

			////////////////////CREATING MENU///////////////////
	do
	{
		fflush(stdin);
		printf("logging in 1%%||||||||||||||||||||||\n");
		printf("\t\     ||||||||||||||||||||||100%%.\nSucceeded.\n");
		printf("Welcome to student management system!\n\nMenu:\n");
		printf("press '1' to print all students names & total students\n");		
		printf("press '2' to print students name with highest avarage\n");		
		printf("press '3' to add student\n");									
		printf("press '4' to add student to specific place\n");					
		printf("press '5' to remove student\n");								
		printf("press '0' to log off\n");										
		printf("Write here your choice: ");
		scanf("%c", &choice);

		switch (choice)
		{
		case '1':
			print_total(da);
			printf("all students are printed succefully\n");
			break;
		case '2':
			print_HighestAvarage(da);
			break;
		case '3':
			printf("Please enter student name: ");
			scanf("%s", &name);
			printf("Please enter student id: ");
			scanf("%s", &id);
			CreateStudent(name, id, &temp);
			index = isEmpty(da);
			arrInsertAt(da, index, temp);
			break;
		case '4':
			printf("Please enter the location for insert: ");
			scanf("%d", &index);
			printf("Please enter student name: ");
			scanf("%s", &name);
			printf("Please enter student id: ");
			scanf("%s", &id);
			CreateStudent(name, id, &temp);
			arrInsertAt(da, index, temp);
			break;
		case '5':
			printf("enter the location of student for remove to: ");
			scanf("%d", &index);
			arrRemoveAt(da, index);	
			break;
		case '0':
			printf("logging off 1%%||||||||||||||||||||||\n");
			printf("\t\      ||||||||||||||||||||||100%%\nSucceeded.\nGoodBye\n");
			FLAG = 0;
			getch();
			break;
		default:
			printf("\n####### ERROR_1114440033 : typed an incorrect character, try again >>>>> \n\n");
			break;
		} 
	} while (FLAG);
	Result destroy_dArray(da);
	return TRUE;
}