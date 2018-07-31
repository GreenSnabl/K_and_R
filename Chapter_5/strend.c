#include <stdio.h>


int mystrlen(char* c)
{
	int len = 0;
	while (*c++ != '\0')
		++len;
	return len;
}

int strend(char* s, char* t)
{
	int same = 0;
	
	int s_len = mystrlen(s);
	int t_len = mystrlen(t);
	
	int index = s_len - t_len;

	if (index < 0)
		return same;
	else {
		same = 1;
		while (*(s + index) != '\0' && *t != '\0') {
			if (*(s + index) != *t)
				return 0;
			s++;
			t++;
		}
	}
	return same;
		
}


int main()
{
	char* a = "affenmaffen";
	char* b = "affen";

	printf("%d\n", strend(a,b));

}

