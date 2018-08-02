/* Error signaling in this version is different to the first in two ways.
 *
 * First, 
 *
 * the diagnostic output by fprintf is directed to stderr instead of stdout, which is
 * the default with printf.
 * That means that if there's something wrong, the error message will be delivered
 * to the screen instead of into a faulty pipeline or the file into the program was writing.
 *
 *
 * Second,
 *
 * the program uses the standard library function exit, which terminates program execution when it is called.
 * The argument of exit is available to whatever process called this one, so the success or failure of the
 * programm can be tested by another program that uses this one as a subprocess.
 *
 *
 * int ferror(FILE *fp)
 *
 * ferror returns non-zero if an error occurs on the stream fp
 */


#include <stdlib.h>
#include <stdio.h>

/* cat: concatenate files, version 2 */
int main(int argc, char* argv[])
{
	FILE *fp;
	void filecopy(FILE *, FILE *);
	
	char *prog = argv[0];	/* program name for errors */


	if (argc == 1)	/* no args; copy standard input	*/
		filecopy(stdin, stdout);
	else
		while (--argc > 0)
			if ((fp = fopen(*++argv, "r")) == NULL) {
				fprintf(stderr, "%s: can't open %s\n",prog, *argv);
				exit(1);
			}
			else {
				filecopy(fp, stdout);
				fclose(fp);
			}
	if (ferror(stdout)) {
		fprintf(stderr, "%s: error writing stdout\n", prog);
		exit(2);
	}
	exit(0);
}

void filecopy(FILE *fp1, FILE *fp2)
{
	int c;

	while (( c = fgetc(fp1)) != EOF)
			putc(c, fp2);
}
