//////////////////////////////////////////Roni Polisanov 307835884 Amit Shwartz 305432775//////////////////////////////////////////
#ifndef _M_DARRAY_
#define _M_DARRAY_
#include "m_student.h"
#include <stdio.h>

typedef struct DynamicArray* DA;

DA create_dArray(int capacity);	 //will create a new dynamic array to be used.
Result read_from_file(char *argv[1], DA da);
Result destroy_dArray(DA da);
Result arrRemoveAt(DA da, int index);
Result arrInsertAt(DA da, int index, ST element);
ST arrGetElementAt(DA da, int index);
Result print_total(DA da);
int getSize(DA da);
Result isEmpty(DA da);
Result print_HighestAvarage(DA da);


#endif