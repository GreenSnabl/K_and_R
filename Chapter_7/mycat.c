#include <stdio.h>

/* cat: concatenate files, version 1 */
int main(int argc, char* argv[])
{
	FILE *fp;
	void filecopy(FILE *, FILE *);

	if (argc == 1)	/* no args; copy standard input	*/
		filecopy(stdin, stdout);
	else
		while (--argc > 0)
			if ((fp = fopen(*++argv, "r")) == NULL) {
				printf("cat: can't open %s\n", *argv);
				return 1;
			}
			else {
				filecopy(fp, stdout);
				fclose(fp);
			}
	return 0;
}

void filecopy(FILE *fp1, FILE *fp2)
{
	int c;

	while (( c = fgetc(fp1)) != EOF)
			putc(c, fp2);
}
