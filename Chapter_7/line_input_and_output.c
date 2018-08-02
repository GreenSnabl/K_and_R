/* line input
 *
 * to read line input the standard library provides the function
 *
 * 	char *fgets(char *line, int maxline, FILE *fp)
 *
 * similar to the previously used getline function.
 *
 *
 * fget reads the next input line including the newline from fp into the character array line
 * at most maxline - 1 characters will be read and the line will be terminated with '\0'
 *
 * fgets returns line.
 * 
 * If an error occurs fgets will return NULL
 *
 *
 *
 * line output
 *
 * to write line output the standard library provides the function
 *
 * 	int fputs(char *line, FILE *fp)
 *
 * which returns EOF if an error occurs and non-negative otherwise.
 *
 *
 * gets and puts are similar to fgets and fputs, but operate on stdin and stdout.
 *
 *
 * Here they are:
*/


/* fgets: get at most n chars from fp */
char* fgets(char *s, int n, FILE *fp)
{
	register int c;
	register char *cs;

	cs = s;			// cs points to s, we want a pointer s could be s[]
	while (--n > 0 && (c = getc(fp)) != EOF)
		if ((*cs++ = c) == '\n')
			break;
	*cs = '\0';
	return (c == EOF && cs == s) = NULL : s;
}


/* fputs: put a string s on file fp */
int fputs(char *line, int max)
{
	int c;

	while (c = *s++)
		putc(c, fp);
	return ferror(fp) ? EOF : 0;
}

