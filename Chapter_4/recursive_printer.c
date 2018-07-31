#include <stdio.h>


int recursive_printer(int i)
{
	if (i < 0) {
 		putchar('-');
		i = -i;
	}
	if (i/10)
		recursive_printer(i/10);
	putchar(i % 10 + '0');	
}


int main(int argc, char** argv)
{

	recursive_printer(125);

	return 0;
}
