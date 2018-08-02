/*	low level IO with read and write
 *
 *	read and write are system calls for input and output accessed from C programs through
 *
 *		int read(int fd, char *buf, int n);
 *		int write(int fd, char *buf, int n);
 *
 * 	
 * 	int fd		-	file descriptor
 * 	char *buf	-	character array where data is to be stored or read from
 * 	int n		-	number of bytes to be transfered
 *
 * 	Each call returns the number of bytes transferred.
 *
 * 	Reading:
 * 		The number of bytes returned may be less than requested
 * 		A return value of zero implies END OF FILE 
 * 		A return value of -1 implies an error.	
 *
 * 	Writing:
 * 		The return value equals the number of bytes written
 * 		An error occured if the bytes written isn't equal to the number requested
 *
 *
 * 	Any number of bytes can be read or written in one call.
 *
 * 	Typically:
 * 			1	-	"unbuffered"
 *	       1024, 4096	-	physical block size
 *
 *	Larger sizes will be more efficient since there will be less system calls to be made
 */
