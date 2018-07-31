#include <ctype.h>
#include <stdio.h>
#include <string.h>
#define MAX_LEN 10

double atof(char* num);


int main(int argc, char** argv)
{
	int len;
	double res;
	char buff[MAX_LEN];
	
	if (argc > 1 && (len = strlen(argv[1])) <= MAX_LEN) {
//		strcpy(buff, argv[1]);
		
		for (int i = 0; i < len; ++i)
		{
			buff[i] = argv[1][i];		
		}
		
		res = atof(buff);
		printf("%f\n", res);
	}
}

double atof(char* s)
{
	double val, power;
	
	int sign, i, exp, expSign;
	for (i = 0; isspace(s[i]); ++i);
	
	sign = (s[i] == '-') ? -1 : +1;
	
	if (s[i] == '-' || s[i] == '+')
		i++;
	for (val = 0.0; isdigit(s[i]); ++i)
		val = 10.0 * val + (s[i] - '0');
	if (s[i] == '.')
		i++;
	for (power = 1.0; isdigit(s[i]); ++i) {
		val = 10.0 * val + (s[i] - '0');
		power *= 10;
	}
	if (s[i] == 'e' || s[i] == 'E')
		++i;
	expSign = (s[i] == '-') ? -1 : +1;

	if (s[i] == '-' || s[i] == '+')
		i++;
	for (exp = 0; isdigit(s[i]); ++i)
	{
		exp = 10 * exp + (s[i] - '0');
	}
	for (int j = 0; j < exp; ++j)
	{
		if (expSign == -1)
			power *= 10.0;
		else 
			power /= 10.0;
	}
	return sign * val / power;
}
