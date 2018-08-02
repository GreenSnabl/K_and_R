/* collect information / pack several objects into a single machine word by
 *
 * defining bitmasks*/
#include <stdio.h>


#define ACC_IN 		01
#define ACC_OUT 	02
#define TOGGLE		04
#define EXTERNAL	010

#define MASSIVE_POWER	07777

/* or per enum */

enum { SP_IN = 01, SP_OUT = 02, STATIC = 04 };


/* instead of defines and enums it is also possible to use a "bit-filed" which is a set
 * of adjacent bits within a signle implementation-defined storage unit, a "word".
 *
 * Replacment for the defines:		*/

struct {
	unsigned int is_acc_in	:	1;	// number after the colon represents the field width in bits
	unsigned int is_acc_out :	1;	// variable bit_field_flags thus contains four 1-bit fields 
	unsigned int is_toggle	:	1;
	unsigned int is_external:	1;
	unsigned int		:	2;	// fields without a name can be used for padding
	unsigned int		:	0;	// special width 0 may be used to force alignment with the next word boundary
} bit_field_flags;	
							
						// advantageous about this approach is it's more natural readability
						// bit-fields can be referenced like outher structure members
						// ie.: bit_field_flags.is_acc_in = 1;



void turn_on_the_light()
{
	printf("woosh\n");
}


int main (void)
{

/* turning on and off the bits with bitwise operations: */
	char flags = 0;
	unsigned int more_flags = 0;
	unsigned int even_more_flags = 0;

	flags |= ACC_IN | TOGGLE;		// compound operator flags = flags | (ACC_IN | TOGGLE);
       						// turn on the ACC_IN and TOGGLE bits	
	
	printf("%d\n", flags);			// should be 5

	flags &= ~(ACC_IN | TOGGLE);		// compound operator flags = flage & ~(ACC_IN | TOGGLE);
						// ACC_IN and TOGGLE bits are set to 0 by the ones complement operator ~
						// bit wise AND with flags yields 0 on their respective positions within flags

	printf("%d\n", flags);			// should be 0
	
	more_flags |= MASSIVE_POWER;	
	
	if ((more_flags & even_more_flags) == 0)	// use bitwise operations to check conditions
		printf("flags are one complemented!\n");

	if ((flags & (ACC_IN | TOGGLE)) == 0)
		printf("ACC_IN and TOGGLE are turned off\n");

	
	bit_field_flags.is_acc_out = 0;
	bit_field_flags.is_acc_in = 1;
	bit_field_flags.is_external = 1;
	
	if ((bit_field_flags.is_acc_out | bit_field_flags.is_acc_in) & bit_field_flags.is_external)
		printf ("ACC in use by external power\n");


	return 0;
}


