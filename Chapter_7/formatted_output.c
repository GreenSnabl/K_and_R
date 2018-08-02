/*	formatted output with int printf(char *format, arg1, arg2, ..);
 *
 *	or 
 *	int fprintf(FILE *fp, char *format, arg1, arg2, ..)
 *	int sprintf(char *string, char *format, arg1, arg2, ..)
 *
 *
 *	printf converts, formats and prints its arguments on the standard output
 *	under control of the format. It returns the number of the characters printed.
 *
 *
 *	Formatting options
 *
 *	printf("%.*s", max, s);
 *
 *	Conversion specification begins with % and ends with conversion character
 *	% 	- begin conversion spec
 *	- 	- left adjustment
 *      number 	- specifies minimum field width. padding on left (or right if left adj. is set) 
 *	. 	- seperate field width from precision
 *      hl 	- h if int is to be printed as short or l if integer is to be printed as long
 *	
 *	Conversion characters:
 *	
 *	d,i	- int; 		signed 	 decimal number
 *	o	- int; 		unsigned octal number
 *	x, X	- int, 		unsigned hexadecimal number
 *	u	- int; 		unsigned decimal
 *	c	- int; 		single char
 *	s	- char *; 	character string
 *	f	- double;	[-]m.dddddd	number of ds given by precision	
 *	e, E	- double;	[-]m.dddddde+/-xx or [-]m.ddddddE+/-xx
 *	g, G	- double;	
 *	p	- void *;	pointer	
 *
 *
 *
 *
 * :%s:			:hello, world:
 * :%10s:		:hello, world:
 * :%.10s:		:hello, wor:
 * :%-10s:		:hello, world:
 * :%.15s:		:hello, world:
 * :%-15s:		:hello, world   :
 * :%15.10s:		:     hello, wor:
 * :%-15.10s:		:hello, wor     :
*/

#include <stdio.h>

int main(void)
{
	int num1 = 12;
	int num1o = 07;
	int num1x = 0xf7;
	double num2 = 7.3452;
	float num3 = -7.23454;
	double num4 = 7.0000012;
	double *num4p = &num4;
	char *str = "Hello, number ";

	printf("%-12.6s%d\n", str, num1);
	printf("%12.3s,%f\n", str, num2);
	printf("%s%o\n", str, num1);
	printf("%s%d\n", str, num1x);
	printf("%s%.2E\n", str, num3);
	printf("%s%.10G\n", str, num4);
	printf("%s%p\n", str, num4p);

}

