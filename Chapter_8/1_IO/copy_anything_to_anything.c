#include <unistd.h>	// for system calls
#include <stdio.h>	// for BUFSIZ

/* copy input to output */
int main(void)
{
	char buf[BUFSIZ];
	int n;
	
	while ((n = read(0, buf, BUFSIZ)) > 0)
		write (1, buf, n);
	return 0;
}
