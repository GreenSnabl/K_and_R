#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAXWORD 100

struct tnode *addtree(struct tnode *, char *);
void treeprint(struct tnode *);
int getword(char*, int);
struct tnode *talloc(void);
char *mystrdup(char *);



struct tnode {
	char *word;
	int count;
	struct tnode *left;
	struct tnode *right;
};


int main(int argc, char** argv)
{
	struct tnode *root;
	char word[MAXWORD];

	root = NULL;
	while (getword(word, MAXWORD) != EOF)
		if (isalpha(word[0]))
			root = addtree(root, word);
	treeprint(root);
	return 0;
}

/* addtree: add a node with w, at or below p */
struct tnode *addtree(struct tnode *p, char *w)
{
	int cond;
	
	if (p == NULL) {		// a new word has arrived
		p = talloc();		// allocate memory space
		p->word = mystrdup(w);
		p->count = 1;
		p->left = p->right = NULL;	
	} 
	else if ((cond = strcmp(w, p->word)) == 0) {	// word already exists
		p->count++;
	}
	else if (cond < 0)				// less than into left subtree
		p->left = addtree(p->left, w);
	else
		p->right = addtree(p->right, w);
	return p;
}

void treeprint(struct tnode *p)
{
	if (p != NULL)
	{
		treeprint(p->left);
		printf("%4d %s\n", p->count, p->word);
		treeprint(p->right);
	}
}

/* talloc: make a tnode */
struct tnode *talloc(void)
{	// return a tnode - pointer to memory space allocated in the size of a struct tnode
	// also malloc meets alignment requirements
	return (struct tnode *) malloc (sizeof(struct tnode));
}

char *mystrdup(char *s)	/* make duplicate of s */
{
	char *p;

	p = (char *) malloc (strlen(s) + 1);	/* +1 for '\0' */
	if (p != NULL)				/* malloc returns NULL if no space is available */
		strcpy(p, s);
	return p;
}

