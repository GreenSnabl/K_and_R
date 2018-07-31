#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "calc.h"

#define MAXOP 100

extern int sp;
extern double val[];

int main(int argc, char* argv[])
{
	int type;
	double op2;
	char s[MAXOP];

	while ((type = getop(s)) != EOF) {
		switch (type) {
			case NUMBER:
				push(atof(s));
				break;
			case '+':
				push(pop() + pop());
				break;
			case '*':
				push(pop() * pop());
				break;
			case '-':
				op2 = pop();
				push(pop() - op2);
				break;
			case '/':
				op2 = pop();
				if (op2 != 0.0)
					push(pop() / op2);
				else
					printf("Error: Zero division!\n");
				break;
			case '%':
				op2 = pop();
				if (op2 != 0.0) {
					double op1 = pop();
					push (op1 - (int)(op1 / op2) * op2);
				}
				else
					printf("Error: Modulo error!\n");
				break;
			case 'p':
				if (sp > 0)
					printf("top most elements of the stack: %f and %f\n", val[sp-1], val[sp-2]);
				else
					printf("not enough elements on the stack\n");
				break;	
			case '\n':
				printf("\t%.8g\n", pop());
				break;

			default:
				printf("Unknown command: %s\n", s);
				break;
		}
	}
	return 0;
}


