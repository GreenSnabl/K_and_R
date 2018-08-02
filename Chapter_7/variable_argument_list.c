#include <stdarg.h>
#include <stdio.h>

/* minprintf:	minimal printf with variable argument list	*/
void minprintf (char *format, ...)
{
	va_list argp;	/* points to each unnamed arg in turn */
	char *p, *sval;
	int ival;
	double dval;

	va_start(argp, format);		/* make argp point to first unnamed arg */
	for (p = format; *p; p++)
	{
		if (*p != '%') {	/* if *p isn't a conversion specifier, go on and print to stdout */
			putchar(*p);
			continue;
		}

		switch (*++p)
		{
			case 'd':
				ival = va_arg(argp, int);
				printf("%d", ival);
				break;
			case 'f':
				dval = va_arg(argp, double);
				printf("%f", dval);
				break;
			case 's':
				for (sval = va_arg(argp, char*); *sval; sval++)		// print the whole string
					putchar(*sval);
				break;
			default:
				putchar(*p);
				break;
		}
	}
	va_end(argp);	/* clean up when done */
}


int main (void)
{
	minprintf("%d, %f, %s.\nThis went well, nice.\n", 123, 0.43343, "neat");
	return 0;
}
