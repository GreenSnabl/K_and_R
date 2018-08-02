#include <unistd.h>
#include <fcntl.h>
#define PERMS	0666

#define NULL		0
#define EOF		(-1)
#define BUFSIZ		1024
#define OPEN_MAX	20	// max #files open at once

typedef struct _iobuf {
	int cnt;	// characters left
	char *ptr;	// next character position
	char *base;	// location of buffer
	int flag;	// mode of file access
	int fd;		// file descriptor
} FILE;
extern FILE _iob[OPEN_MAX];

#define stdin	(&_iob[0])
#define stdout	(&_iob[1])
#define stderr	(&_iob[2])

enum _flags {
	_READ	=	01,	// file open for reading
	_WRITE	=	02,	// file open for writing
	_UNBUF	=	04,	// file is unbuffered
	_EOF	=	010,	// EOF has occurred on this file
	_ERR	=	020	// error occurred on this file
};

int _fillbuf(FILE *);
int _flushbuf(int, FILE *);

#define feof(p)		(((p)->flag & _EOF) != 0)
#define ferror(p)	(((p)->flag & _ERR) != 0)
#define fileno(p)	((p)->fd)

#define getc(p)		(--(p)->cnt >= 0 \
			? (unsigned char) *(p)->ptr++ : _fillbuff(p))

/* (--(p)->cnt >= 0) 			decrement the character count
 * (unsigned char) *(p)->ptr++		return the pointed at position cast as unsigned char
 * 					and advance the pointer
 * __fillbuff(p)			allocate and fill buffer, return char from it
*/

#define putc(x,p)	(--(p)->cnt >= 0 \
			? *(p)->ptr++ = (x) : _flushbuf((x),p))

/* (--(p)->cnt >= 0) 			decrement the character count
 * *(p)->ptr++ = (x)			put x into the actual buffer position and advance ptr
 *
 * _flushbuf((x), p)			reset the structure contents and put x into the
 * 					cleared buffer
 */


#define getchar()	getc(stdin)
#define	putchar(x)	putc((x), stdout)

FILE *fopen(char *name, char *mode)
{
	int fd;
	FILE *fp;

	if (*mode != 'r' && *mode != 'w' && *mode != 'a')
		return NULL;					// if mode is anything but 
								// the possible options -> abort
	for (fp = _iob; fp < _iob + OPEN_MAX; fp++)
		if ((fp->flag & (_READ | _WRITE)) == 0)		// slot where flags are not set, yet?
			break;					// found free slot
	if (fp >= _iob + OPEN_MAX)				// fp points beyond array bounds?
		return NULL;					// cya

	if (*mode == 'w')
		fd = creat(name, PERMS);			// creat(e) new file
	else if (*mode == 'a') {
		if ((fd = open(name, O_WRONLY, 0)) == -1)	// fill not yet existing?
			fd = creat(name, PERMS);		// creat(e) it
		lseek(fd, 0L, 2);				// whether fill was existing or was just created,
	}							// move the file pointer to the end of it
	else 
		fd = open(name, O_RDONLY, 0);			// file exists!
	if (fd == -1)						// but couldn't access it
		return NULL;
	fp->fd 	= fd;						//
	fp->cnt = 0;						//	fill out
	fp->base = NULL;					//	the struct
	fp->flag = (*mode == 'r') ? _READ : _WRITE;		//	informations
	return fp;
}


/* _fillbuff: allocate and fill input buffer */
int _fillbuff(FILE *fp)
{
	int bufsize;

	if ((fp->flag & (_READ | _EOF | _ERR)) != _READ)
		return EOF;
	bufsize = (fp->flag & _UNBUF) ? 1 : BUFSIZ;
	if (fp->base == NULL)
		if (fp->base = (char *) malloc(bufsize) == NULL)
			return EOF;
	fp->ptr = fp->base;
	fp->cnt = read(fp->fd, fp->ptr, bufsize);		// int read(int fd, char *buf, int n)
	if (--fp->cnt < 0) {					// decrement count of buffered chars in any way
		if (fp->cnt == -1)				// if count is < 0 it might have 2 possible sources
			fp->flag |= _EOF;			// read file is read completely
		else
			fp->flag |= _ERR;			// or there has been an error -> fp->cnt = read(..) returned -1 
		fp->cnt = 0;					// and now it's -2 after --fp->cnt
		return EOF;
	}
	return (unsigned char) *fp->ptr++;			// if all went well return the currently pointed at char
}								// and advance the pointer


FILE _iob[OPEN_MAX] = {	// initialize the first 3 elements of _iob: stdin, stdout, stderr
	{ 0, (char *) 0, (char *) 0, _READ, 0	},
	{ 0, (char *) 0, (char *) 0, _WRITE, 1	},
	{ 0, (char *) 0, (char *) 0, _WRITE | _UNBUF, 2}
};

}
