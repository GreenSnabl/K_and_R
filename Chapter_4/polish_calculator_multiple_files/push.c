#include <stdio.h>
#include "calc.h"

#define MAXVAL 100

int sp = 0;		// Stack pointer
double val[MAXVAL];

void push(double f)
{
	if (sp < MAXVAL)
		val[sp++] = f;
	else
		printf("Error: Stack is full! Can't push %g\n", f);
}

double pop()
{
	if (sp > 0)
		return val[--sp];
	else
		printf("Stack is empty, can't pop.\n");
		return 0.0;
}
