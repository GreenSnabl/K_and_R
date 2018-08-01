#include <stdio.h>

/* quick implementation of an empty ascending stack */

#define BUFSIZE 1000

static int bufp = 0;
static char buf[BUFSIZE];

int getch()
{
	return (bufp > 0) ? buf[--bufp] : getchar();	
}

void ungetch(int c)
{
	if (bufp >= BUFSIZE)
		printf("Error: Buffer is full!\n");
	else
		buf[bufp++] = c;
}
