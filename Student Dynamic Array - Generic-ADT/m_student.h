//////////////////////////////////////////Roni Polisanov 307835884 Amit Shwartz 305432775//////////////////////////////////////////
#ifndef _M_STUDENT_
#define _M_STUDENT_
#define N_SIZE 27
#define T_SIZE 10
#define B_SIZE 100
#include <stdio.h>

typedef enum {FALSE, TRUE} Result;
typedef struct Student* ST;

Result CreateStudent(char *name, char *id, ST* student);
int stAddGrade(ST student, char* token, int count);
ST std_array(int capacity);
Result destroyStudent(ST students);
float getStudentAverage(ST students);
Result print_students(ST students);


#endif