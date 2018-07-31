/* Conditional defines can be used to include code depending
 * on the current operating system, environment */

#if SYSTEM == SYSV
	#define HDR "sysv.h"
#elif SYSTEM == BSD
	#define HDR "bsd.h"
#elif SYSTEM == MSDOS
	#define HDR "msdos.h"
#else
	#define HDR "default.h"
#endif
#include HDR
