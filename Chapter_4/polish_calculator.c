#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


#define MAXOP 100
#define NUMBER '0'
#define MAXVAL 100
#define BUFSIZE 100


int getch(void);
void ungetch(int);

int getop(char[]);
void push(double);
double pop(void);

int sp = 0;		// Stack pointer
double val[MAXVAL];



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

char buf[BUFSIZE];
int bufp = 0;		// Bufferpointer


int getch(void)
{
	return (bufp > 0) ? buf[--bufp] : getchar();	
}

void ungetch(int c)
{
	if (bufp >= BUFSIZE)
		printf("ungetch: too many characters\n");
	else
		buf[bufp++] = c;
}
