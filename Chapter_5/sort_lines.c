#include <stdio.h>
#include <string.h>

#define MAXLINES 5000		/* max #lines to be sorted */

char *lineptr[MAXLINES];	/* pointers to text lines  */

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);

void qsort(char *lineptr[], int left, int right);

/* sort input lines */

int main(int argc, char** argv)
{
	int nlines;

	if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
		qsort(lineptr, 0, nlines - 1);
		writelines(lineptr, nlines);
		return 0;
	} else {
		fprintf(stderr, "error: input too big to sort!\n");
		return 1;
	}
}

#define MAXLEN 1000
int mygetline(char *, int);
char *alloc(int);

/* readlines: read input lines */
int readlines(char *lineptr[], int maxline)
{
	int len, nlines;
	char *p, line[MAXLEN];

	nlines = 0;
	while ((len = mygetline(line, MAXLEN)) > 0) {
			if (nlines >= maxline || (p = alloc(len)) == NULL)
				return -1;
			else {
				line[len-1] = '\0';	// delete newline
				strcpy(p, line);
				lineptr[nlines++] = p;
			}
	}
	return nlines;		
}

void writelines(char *lineptr[], int nlines)
{
	int i;
	for (i = 0; i < nlines; ++i)
		printf("%s\n", lineptr[i]);
}

void qsort(char *v[], int left, int right)
{
	int i, last;
	void swap(char *v[], int i, int j);

	if (left >= right)
		return;
	swap(v, left, (left + right)/2);
	last = left;
	
	for (i = left + 1; i <= right; i++)
		if (strcmp(v[i], v[left]) < 0)
			swap(v, ++last, i);

	swap(v, left, last);
	qsort(v, left, last-1);
	qsort(v, last+1, right);
}

void swap(char *v[], int i, int j)
{
	char *temp;

	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}
