/*	formatted input with
 *
 *	int scanf(char *format, ...);
 *
 *	or
 *	int fscanf(FILE* fp, char *format, arg1, arg2, ...);
 *	int sscanf(char *string, char *format, arg1, arg2, ..);
 *
 *	the three functions return the number of successfully converted and stored arguments as int
 *
 *
 *	scanf reads characters from the standard input, interprets them according to the specification
 *	in format and stores the results through the remaining arguments.
 *	Each argument must be a pointer to the place wherer the corresponding converted input should be stored
 *	means:
 *
 *	scanf("%X, %.4f, %-5.10s", &someInt, &someDouble, someCharString);
 *
 */

#include <stdio.h>

int main(void)
{	/* rudimenatry calculator */
	double sum, v;

	sum = 0;
	while (scanf("%lf", &v) == 1)
		printf("\t%.2f\n", sum += v);
	return 0;

}
