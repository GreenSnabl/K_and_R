/*	
 *	other than the default input, output and error, you must
 *	explicitly open files in order to read or write them.
 *
 *	There are two ways to do this, both return a file descripor, if
 *	successful
 *
 * OPEN
 *	int open(char *name, int flags, int perms);
 *
 * ex:
 *	fd = open(name, O_RDONLY, 0);
 *
 *	flags:
 *		- O_RDONLY
 *		- O_WRONLY
 *		- O_RDWR
 *
 *	defined in <sys/file.h>
 *
 *	for all cases in K&R the perms argument for open will be 0.
 *
 *	If you try to open a file that does not exist open will return -1
 *	error.
 *
 *
 * CREAT
 * 	int creat(char *name, int perms);
 *
 * 	creat is used to create new files or to rewrite old ones.
 *
 * ex:
 *	fd = creat(name perms)
 *
 *	
 *	creat returns a file descriptor if successful and -1 if not. If the file
 *	already exists it will be truncated to zero length, thereby discarding 
 *	its previous contents. !DANGER!
 *
 *
 * PERMISSIONS (int perms)
 *
 *
 * 		     octal notation
 * 		       4 * 3 bits
 *
 * 	---------- 	0000 	no permissions
 * 	-rwx------ 	0700 	read, write, & execute only for owner
 * 	-rwxrwx--- 	0770 	read, write, & execute for owner and group
 * 	-rwxrwxrwx 	0777 	read, write, & execute for owner, group and others
 * 	---x--x--x 	0111 	execute
 * 	--w--w--w- 	0222 	write
 * 	--wx-wx-wx 	0333 	write & execute
 * 	-r--r--r-- 	0444 	read
 * 	-r-xr-xr-x 	0555 	read & execute
 * 	-rw-rw-rw- 	0666 	read & write
 * 	-rwxr----- 	0740 	owner can read, write, & execute; 
 * 				group can only read; others have no permissions 
 */

#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>
#include <fcntl.h>
#include <stdlib.h>

#define PERMS 0666	/* RW for owner, group, others */

void error(char *, ...);

/* copy file1 to file2 */
int main (int argc, char *argv[])
{
	int fd1, fd2, n;
	char buf[BUFSIZ];
	
	if (argc != 3)
		error("Usage: cp from to");
	if ((fd1 = open(argv[1], O_RDONLY, 0)) == -1)
		error("cp: can't open %s", argv[1]);
	if ((fd2 = creat(argv[2], PERMS)) == -1)
		error("cp: can't create %s, mode %03o", argv[2], PERMS);
	while ((n = read(fd1, buf, BUFSIZ)) > 0)
		if (write(fd2, buf, n) != n)
			error("cp: write error on file %s", argv[2]);
	return 0;
}


/* error is called with variable argument list like printf
 *
 * The implementation of error illustrates how to use another member of the printf family
 *
 * 	vprintf
 *
 * it is like printf, but instead of the variable argument list is replaced by a single argument
 * that hs been initialize by calling the va_start macro
 */

void error(char *format, ...)
{
	va_list args;

	va_start(args, format);
	fprintf(stderr, "error: ");
	vfprintf(stderr, format, args);
	fprintf(stderr, "\n");
	va_end(args);
	exit(1);
}

