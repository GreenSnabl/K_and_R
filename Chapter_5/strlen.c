#include <stdio.h>

#define printd(expr) printf(#expr " = %d\n", expr)

int mystrlen(char* c)
{
	int n;
	for (n = 0; *(c+n) != '\0'; ++n)
		;
	return n;
}

int main(int argc, char** argv)
{
	if (argc > 1) {
	char* c = argv[1];
	printd(mystrlen(c));
	}
	else {
		printf("Second argument needed!\n");
	}
	return 0;

}
