#include <stdio.h>

int func(int a)
{
	return 6;
}


#define YES "yep yep yiep\n"
#define FOREVER for (;;)
#define max(A, B) ((A > B) ? (A) : (B))
#define NOONELIVESFOREVER(A) ((A > 20) ? (1) : (0))
#define func(a) 5					// overwrites the function func(int a)



/* preprocessor operator #	*/

#define dprint(expr) printf(#expr " = %d\n", expr)	// if a parameter is preceded by a # in the replacement text the combination will be
							// expanded into a quoted string
							//
							// the lefthand macro expands to dprint("123")  	= printf("123" " = %d\n", 123)
							// and the strings will automatically concatenated	  printf("123 = %d\n", 123)


/* preprocessor operator ##	
 *
 * ## provides a way to concatenate actual arguments during macro expansion */

#define paste(a,b) a ## b				// paste(name, 1) creates the token name1


/* macro block structure with "\"
 *
 * macros can span multiple lines by using "\" */

#define swap(t, a, b) t c = b; \
			    b = a; \
			    a = c;


int main()
{
	printf(YES);		// macro substitution
	printf("YES\n");		// no macro substitution

	int a = 10;
	int b = 15;

	FOREVER {
		printf("%d\n", max(a,b));
		if (NOONELIVESFOREVER(a++)) break;		// using sideeffects within macros is dangerous!
	}							// NOONELIVESFOREVER(10++) evaluetes to ((10++ 	> 20) ? (1) : (0))
	a = 11, b = 10;						//					((11 	> 20) ? (1) : (0))
	max(a--, b--);						// BUT
	printf("a = %d, b = %d\n", a, b);				// max(11--, 10--) evaluates to		((11-- > 10--) ? 10-- : 10--)
								// 					((10 > 9) ? 10-- : 9--)
								// 	with 	a = 9 and b = 9 since the return value will be evaluated twice
	
	/* with #undef it is possible to undefine macros */
	
	printf("%d\n", func(a));

	#undef func					// undefine the macro and assure that func(a) will be a function call

	printf("%d\n", func(a));

	dprint(max(a,b));

	int paste(var, 1) = 10;
	
	dprint(var1);
	
	int ja = 123;
	int nein = 321;

	swap(int, ja, nein);
	
	dprint(ja);
	dprint(nein);

}
