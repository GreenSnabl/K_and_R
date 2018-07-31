/* Here we write our own allocation and free functions
 * other then the c library functions we do not use
 * syscalls to aquire memory space from the os, but
 * use a predefined memory block "allocbuf" instead.
 *
 *
 * allocbuf:
 *    ____allocated__________free_____
 *   |__|____|__|_____||______________|
 *   		|      |
 *   	        p    allocp
 *
 */

#define ALLOCSIZE 10000 	  // maximum storage

/* static variables only visible for this source file */
static char allocbuf[ALLOCSIZE];  // storage for alloc
static char *allocp = allocbuf;  // next free position

char *alloc(int n)		  // return pointer to n characters
{
	if (allocbuf + ALLOCSIZE - allocp >= n)
	{
		allocp += n;		// add n data positions
					// scaled by sizeof(datatype)
					// here sizeof(char) = 1 byte 
		return allocp - n;
	} else	{
		return 0;
	}
}

void afree(char *p)
{
	if (p >= allocbuf && p < allocbuf + ALLOCSIZE)
		allocp = p;
}
