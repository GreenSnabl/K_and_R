#include "calc.h"
#include <stdio.h>
#include <ctype.h>


int getop(char s[])
{
	int i, c;
	while ((s[0] = c = getch()) == ' ' || c == '\t')
		;

	s[1] = '\0';

	if (!isdigit(c) && c != '.')
		return c;	// not a number -> return +,-,*,/,% ..
	i = 0;
	if (isdigit(c))	// collect integer part	
		while (isdigit(s[++i] = c = getch()))	// save in s until non-number is encountered
			;
	if (c == '.')	// collect fraction part
		while (isdigit(s[++i] = c = getch()))	// save in s until non-number is encountered			;
	s[i] = '\0';	// insert delimiter to be able to tell the operands apart
	if (c != EOF)
		ungetch(c);
	return NUMBER;
}
