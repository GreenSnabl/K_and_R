#include <string.h>
#include <stdio.h>


void reverse(char a[])
{
	int len = strlen(a);
	char temp, *p, *pe;
	
	for (char *p = a, *pe = a + len - 1; p <= pe; p++, pe-- )
	{
		temp = *p;
		*p = *pe;
		*pe = temp;	
	}
	printf("%s\n", a);
}


int main()
{
	char word[] = "Hello World!";
	reverse(word);
}
