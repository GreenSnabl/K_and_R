/*	Random access
 *
 *	input and output are typically sequential
 *
 *	when necessary a file can also be read in arbitrary order.
 *
 * 	the system call
 *
 *		long lseek(int fd, long offset, int origin);
 *
 *	provides a way to to set the current position in the file whose descripor
 *	is fs to offset, which is taken relativ to the location specified by origin.
 *
 *	origin can be 0, 1 or 2
 *
 *		0	-	beginning
 *		1	-	current position
 *		2	-	end
 *
 *	The return of lseek is a long that gives the new position in the file
 *	or -1 if an error occurs.
 *
 *	The standard library function
 *
 *		int fseek(FILE *fp, long offset, int origin);
 *
 * 	is similar to lseek but returns non-zero when an error occurs.
 *
 *
 *
 *	example:
 *		to append to a file (the redirection >> in the UNIX shell or
 *		"a" with fopen) one would use
 *
 *		lseek(fd, 0L, 2);
 *
 *	to get back to the beginning:
 *
 *		lseek(fd, 0L, 0);
 *
 *	0L means the same as (long)0
 *
 *	if lseek is properly declared you could also just use 0.
 *
 *
 *	With lseek you can treat files as arrays at the price of slower access.
 */

#include <unistd.h>

/* get: read n bytes from position pos */
int get(int fd, long pos, char *buf, int n)
{
	if (lseek(fd, pos, 0) >= 0)	/* get to pos */
		return read(fd, buf, n);
	else
		return -1;
}
