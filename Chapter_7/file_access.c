/*	file access
 *
 * files can be opend by the library function
 *
 * 	FILE *fopen(char *name, char *mode);
 *
 * fopen returns a pointer to a FILE-structure containing information about
 *
 * 	- location of the buffer
 * 	- current character position in the buffer
 * 	- if file is being read or written to
 * 	- whether error or EOF have occured
 *
 * FILE does not have a structure tag since it is defined with a typedef
 *
 *
 * 	char *name	- string containing the location of the file
 * 	char *mode	- "r" read
 * 			- "w" write
 * 			- "a" append
 * 			- "[rwa]b" read/write/append bytes
 *
 * 	if there is any error fopen will return a NULL-pointer
 */

/* 	read from an opened file
 *
 *
 * the next thing needed is a way to read from and write to that file
 *
 * 	int getc(FILE *fp);
 * 	int putc(int c, FILE *fp)
 *
 *	both functions can be used within a macro to define functions like
 *
 *	int getchar()		and
 *	int putchar(c)
 *
 *	as in
 *
 *	#define getchar()	getc(stdin)
 *	#define putchar(c)	putc((c), stdout)
 */

