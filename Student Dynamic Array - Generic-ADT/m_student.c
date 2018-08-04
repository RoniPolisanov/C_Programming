//////////////////////////////////////////Roni Polisanov 307835884 Amit Shwartz 305432775//////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "m_student.h"

//student's struct
struct Student
{
	char name[N_SIZE];
	char id[T_SIZE];
	int grades[T_SIZE];
};

//creating memory for student
Result CreateStudent(char* name, char* id, ST *students)
{
	int i;
	*students = (ST)calloc(1 , sizeof(struct Student));
	if (*students == NULL) return FALSE;
	strcpy((*students)->name, name);
	strcpy((*students)->id, id);
	return TRUE;
}

//posting grades
int stAddGrade(ST students, char* token, int i)
{
	students->grades[i] = atoi(token);
	return students->grades[i];
}

//making students avarage
float getStudentAverage(ST students)
{
	int  i; 
	float sum=0, avarage, count=0;
	for (i = 0, count = 0; i < 10; i++, count++)
		sum += students->grades[i];

	avarage = sum / count;
	return avarage;
}

//printing students full details
Result print_students(ST students)
{
	int i;
	printf("Name: %s, ID: %s\n", students->name, students->id);
	for (i = 0; i < 10; i++)
		printf("Grade[%d]: %d\n", i, students->grades[i]);
	return TRUE;
}

