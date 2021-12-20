#include "validator.h"
#include <stdio.h>

int main()
{
	unsigned char data[DATA] = {1};
	unsigned char code[ERRORS] = {0};

	validator(code,data);

	printf("Code = ");
	int i;
	for(i=0; i<ERRORS; i++)
	{
		printf("%d \n",code[i]);
	}
	return 0;
}
