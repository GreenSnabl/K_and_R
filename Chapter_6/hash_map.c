#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define HASHSIZE 101
#define MAXWORD 100

struct nlist *lookup(char *);
char *mystrdup(char *);
int getword(char*, int);
struct nlist *install(char *, char *);
int undef(char *);

struct nlist {				/* table entry	*/
	struct nlist *next;		/* next entry in the chain */
	char *name;			/* defined name */
	char *defn;			/* replacement text */
};

int main(void)
{
	char *name1 = "aba";
	char *name2 = "baa";
	char *def1  = "1";
	char *def2  = "2";

	struct nlist *np1, *np2, *np3;
	
	np1 = install(name1, def1);
	if (np1 != NULL)
	{
		printf("Install worked!\n np1->name: %s np1->def: %s\n", np1->name, np1->defn);
	}
	np2 = install(name1, def2);
	if (np1 == np2)
	{
		printf("Installing np2 and thus overwriting np1 worked!\n");
		printf("np1 == np2\n");
		printf("np1->name: %s == np2->name: %s\n", np1->name, np2->name);
		printf("np1->defn: %s == np2->defn: %s\n", np1->defn, np2->defn);
	}
	undef("aba");
	if ((np1 = lookup("aba")) == NULL)
	{
		printf("undef: Success!\n");
	}

}


static struct nlist *hashtab[HASHSIZE];	/* pointer table */

/* hash: form hash value for string s
 *
 * the hash function calculates a hashvalue for a given string by multiplying its character value
 * by 31 and getting the remainder through modulo HASHSIZE
 */

unsigned hash(char *s)
{
	unsigned hashval;

	for (hashval = 0; *s != '\0'; s++)
		hashval = *s + 31 * hashval;
	return hashval % HASHSIZE;
}


/* lookup: look for s in hashtab */
struct nlist *lookup(char *s)
{
	struct nlist *np;

	for (np = hashtab[hash(s)]; np != NULL; np = np->next) // a lot of stuff packed into the for loop
		if (strcmp(s, np->name) == 0)				// use int strcmp(char*, char*)
			return np;
	return NULL;
}

/* install: put (name, defn) in hashtab
 *
 * determine if the name being installed is already present, if so the old definition will be
 * supersed by the new one. Otherwise, a new entry will be created.
 */

struct nlist *install(char *name, char *defn)
{
	struct nlist *np;
	unsigned hashval;

	if ((np = lookup(name)) == NULL) {	/* not found */
		np = (struct nlist *) malloc (sizeof (*np));
		if (np == NULL || (np->name = strdup(name)) == NULL)
			return NULL;
		hashval = hash(name);
		np->next = hashtab[hashval];
		hashtab[hashval] = np;
	}
	else {					/* already there */
		free ((void *) np->defn);	/* free previous defn */
	}
	if ((np->defn = strdup(defn)) == NULL)
		return NULL;
	return np;
}

int undef(char *name)
{
	struct nlist *np1, *np2;

	if ((np1 = lookup(name)) != NULL)
	{
		if (np1->next == NULL) {
			free((void*) np1->name);
			free((void*) np1->defn);
			np1 = NULL;
		}
		else {
			while (strcmp(np2->name, name) != 0)
			{
				np1 = np2;
				np2 = np2->next;
			}
			np1->next = np2->next;
			free((void*) np2->name);
			free((void*) np2->defn);
			np2->next = NULL;
			np2 = NULL;
		}
		return 0;
	}
	else 
		return -1;
}


char *mystrdup(char *s)	/* make duplicate of s */
{
	char *p;

	p = (char *) malloc (strlen(s) + 1);	/* +1 for '\0' */
	if (p != NULL)				/* malloc returns NULL if no space is available */
		strcpy(p, s);
	return p;
}
