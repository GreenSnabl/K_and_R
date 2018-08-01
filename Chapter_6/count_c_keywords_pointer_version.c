#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define MAXWORD 100
#define NKEYS (sizeof keytab / sizeof (struct key))

struct key {
	char *word;
	int count;
} keytab[] = {
	"auto", 0,
	"break", 0,
	"case", 0,
	"char", 0,
	"const", 0,
	"continue", 0,
	"default", 0,
	"define", 0,
	"do", 0,
	"double", 0,
	"else", 0,
	"float", 0,
	"for", 0,
	"if", 0,
	"int", 0,
	"long", 0,
	"NULL", 0,
	"static", 0,
	"struct", 0,
	"unsigned", 0,
	"volatile", 0,
	"while", 0
};


int getword(char *, int);
struct key *binsearch(char *, struct key *, int);

/* count C keywords, pointer version */
int main(void)
{
	char word[MAXWORD];
	struct key *p;

	while (getword(word, MAXWORD) != EOF)
		if (isalpha(word[0]))
			if ((p = binsearch(word, keytab, NKEYS)) != NULL)
				p->count++;		// instead of keytab[n].count++
	for (p = keytab; p < keytab + NKEYS; p++)	// instead of (n = 0; n < NKEYS; n++)
		if (p->count > 0)
			printf("%4d %s\n", p->count, p->word);
	return 0;
}


/* binsearch: find word in tab[0] ... tab[n-1] */
struct key *binsearch(char* word, struct key tab[], int n)
{
	int cond;
	struct key *low = &keytab[0];
	struct key *high = &keytab[n];		// one beyond the last element
	struct key *mid;
	while (low < high) {
		mid = low + (high - low) / 2;
		if ((cond = strcmp(word, mid->word)) < 0)
			high = mid;
		else if (cond > 0)
			low = mid + 1;
		else
			return mid;	
	}
	return NULL;
}
