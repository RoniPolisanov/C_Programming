//////////////////////////////////////////Roni Polisanov 307835884 Amit Shwartz 305432775//////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "m_darray.h"

//dynamic array struct
struct DynamicArray
{
	ST* students;
	int size;
	int capacity;
};

//creating dynamic array
DA create_dArray(int capacity)		//will create a new dynamic array to be used.
{
	DA DaArray = (DA)malloc(1 * sizeof(DA));
	if (DaArray == NULL)
	{
		printf("Memory error 'create_dArray' \n"); return NULL;
	}

	DaArray->size = 0;
	DaArray->capacity = capacity;

	DaArray->students = (ST)calloc(capacity , sizeof(ST));
	if (DaArray->students == NULL)
	{
		printf("Memory error 'stArray' \n"); free(DaArray);  return NULL;
	}

	return DaArray;
}

//reading from file argv[1] (input.txt), creating students and filling grades
Result read_from_file(FILE* fp, DA da)
{
	float avg1 = 0, avg2 = 0, count = 0;
	int i;
	char *token, name[N_SIZE], id[T_SIZE], buff[B_SIZE];
	const char s[] = " ,\n";
	
	if (fp == NULL)
	{
		printf("ERROR input argument\n");
		return FALSE;
	}

	while (fgets(buff, B_SIZE, fp) != NULL)
	{
		token = strtok(buff, s);
		strcpy(name, token);
		token = strtok(NULL, s);
		strcpy(id, token);
		//creating students from file
		CreateStudent(name, id, &da->students[da->size]);
		for (i = 0; i < 10; i++)
		{
			token = strtok(NULL, s);
			if (token == NULL)
				break;
			//fill grades
			stAddGrade(da->students[da->size], token, i);
		}
		da->size++;
	}

}

//printing the highest avarage of all the students
Result print_HighestAvarage(DA da)
{
	int i,location;
	float high=0, temp=0;
	for (i = 0; i < da->capacity; i++)
	{
		if (da->students[i] != NULL)
		{		
			temp = getStudentAverage(da->students[i]);
			if (high < temp)
			{
				high = temp;
				location = i;
			}
		}
	}
	print_students(da->students[location]);
	printf("Avarage: %f\n", high);
	return TRUE;
}

//destroying dynamic array for quit
Result destroy_dArray(DA da)
{
	free(da->students[da->size]);
	free(da);
	if (da == NULL) return TRUE;
	return FALSE;
}

//remove student in index that we choice
Result arrRemoveAt(DA da, int index)
{
	if (index > da->capacity)
	{
		printf("index is not exist, out of bounce");
		return FALSE;
	}
	free(da->students[index]);
	da->students[index] = NULL;
	printf("student  in location: %d, removed from the system\n", index);
	da->size--;
	return TRUE;
}


//add student in index that we choice
Result arrInsertAt(DA da, int index, ST element)
{
	int i, j;
	char token[T_SIZE];
	if (da->capacity < index)
		return FALSE;

	if (da->capacity == index)
	{
		da->students = (DA)realloc( da->students , sizeof(da->students)*(da->capacity+1));
		if (da->students == NULL)
		{
			printf("memory error"); 
			return FALSE;
		}
		da->capacity++;
	}
	da->students[index] = element;
	printf("Remember grades range only between 0-100, otherwise to stop\n");

	for (i = 0; i < 10; i++)
	{
		printf("Grade to add: ");
		scanf("%s", &token);
		j = atoi(token);
		if (j < 0 || j>100) break;

		stAddGrade(da->students[index], token, i);
	}
	da->size++;
	return TRUE;
}

//print all the students that in the system
Result print_total(DA da)
{
	int i = 0;
	for (i = 0; i < da->capacity; i++)
	{
		if (da->students[i] != 0)
		{
			printf("Student Location: %d, ", i);
			print_students(da->students[i]);
		}
	}
	return TRUE;
}

//getting student in index that we choice
ST arrGetElementAt(DA da,int index)
{
	return da->students[index];
}

//get number of students right now
int getSize(DA da)
{
	return da->size;
}

//check if some of students are empty
int isEmpty(DA da)
{
	int i;
	for (i = 0; i < da->capacity; i++)
		if (da->students[i] == NULL)
			return i;
}