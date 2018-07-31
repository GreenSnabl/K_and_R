#include <string.h>
#include <stdio.h>
#include <ctype.h>

#define printd(expr) printf(#expr " = %d\n", expr)

int lexComp (char *a, char* b)
{
	return *a > *b;
}

int sizeDiff(char *a, char* b)
{
	return (strlen(a) - strlen(b));
}

int hasMoreWhiteSpace(char *a, char* b)
{
	int count_a = 0, count_b = 0;
	
	while (*a != '\0')
	{
		if (*a++ == ' ')
			count_a++;
	}
	while (*b != '\0')
	{
		if (*b++ == ' ')
			count_b++;
	}
	return count_a > count_b;
}

int strcmpCaseInsensitive(char *a, char* b)
{
	int i;

	for (i = 0; tolower(a[i]) == tolower(b[i]); i++)
		if (a[i] == '\0')
			return 0;
	return a[i] - b[i];
}


int comp(char* a, char* b, int (*comp)(void*, void*))
{
	return (*comp)(a, b);
}

int main(int argc, char** argv)
{
	char* a = "h e l l o i a m l o t s   o f    w h i t e     s p a c e";
	char* b = "off you go     ";

	printf("%s\n\t\tvs\n%s\n", a, b);

	printd(comp(a,b,(int(*)(void*, void*))(lexComp)));
	printd(comp(a,b,(int(*)(void*, void*))(sizeDiff)));
	printd(comp(a,b,(int(*)(void*, void*))(hasMoreWhiteSpace)));
	printd(comp(a,b,(int(*)(void*, void*))(strcmpCaseInsensitive)));
}
