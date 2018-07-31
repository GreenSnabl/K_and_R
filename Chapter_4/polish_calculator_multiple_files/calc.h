#ifndef calc_h
#define calc_h

#define NUMBER 0

int getch(void);
void ungetch(int);
int getop(char[]);
void push(double);
double pop(void);
#endif
