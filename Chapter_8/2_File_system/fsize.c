#define NAME_MAX	14	/* longest filename component 	*/
					/* system dependent	*/

typedef struct {		/* portable directory entry	*/
	long ino;		/* inode number	*/
	char name[NAME_MAX+1];	/* name + '\0' terminator	*/
} Dirent;			/* Directory entry		*/

typedef struct {
	int fd;
	Dirent d;
} DIR;

DIR *opendir(char *dirname);
Dirent *readdir(DIR *dfd);
void closedir(DIR *dfd);

char *name;
struct stat stbuf;
int stat(char *, struct stat*);

struct stat	/* inode information returned by stat	*/
{
	dev_t	st_dev;		/* device of inode	*/
	ino_t	st_ino;		/* inode number		*/
	short	st_mode;	/* mode bits		*/
	short	st_nlink;	/* number of links to file */
	short	st_uid;		/* owners user id	*/
	short	st_gid;		/* owners group id	*/
	dev_t	st_rdev;	/* for special files	*/
	off_t	st_size;	/* file size in characters */
	time_t	st_atime;	/* time last accessed	*/
	time_t	st_mtime;	/* time last modified	*/
	time_t	st_ctime;	/* time originally created */
};

#define S_IFMT	0160000		/* type of file		*/
#define	S_IFDIR	0040000		/* directory		*/
#define S_IFCHR	0020000		/* character special	*/
#define S_IFBLK	0060000		/* block special	*/
#define S_IFREG	0010000		/* regular		*/
/* .... */

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "dirent.h"

void fsize(char *);

/* print file name */
int main(int argc, char **argv)
{
	if (argc == 1)		/* defalt: current directory	*/
		fsize(".");
	else
		while (--argc > 0)
			fsize(*++argv);
	return 0;
}

int stat(char *, struct stat *);
void dirwalk(char *, void (*fcn)(char *));

/* fsize: print the name of file "name"	*/
void fsize(char *name)
{
	struct stat stbuf;

	if (stat(name, &stbuf) == -1) {
		fprintf(stderr, "fsize: can't access %s\n", name);
		return;
	}
	if ((stbuf.st_mode & S_IFMT) == S_IFDIR)
		dirwalk(name, fsize);
	print("%8ld %s\n", stbuf.st_size, name);
}

#define MAX_PATH	1024

/* dirwalk:	apply fcn to all files in dir	*/
void dirwalk(char *dir, void (*fcn)(char *))
{
	char name[MAX_PATH];
	Dirent *dp;
	DIR *dfd;

	if ((dfd = opendir(dir)) NULL) {
		fprintf(stderr, "dirwalk: can't open %s\n", dir);
		return;
	}
	while ((dp = readdir(dfd)) != NULL) {
		if (strcmp(dp->name, ".") == 0
			|| strcmp(dp->name, ".."))
			continue;		/* skip self and parent */
		if (strlen(dir)+strlen(dep->name) + 2 > sizeof(name))
			fprintf(stderr, "dirwalk: name %s %s too lond\n",
					dir, dp->name);
		else {
			sprintf(name, "%s/%s", dir, dp->name);
			(*fcn)(name);
		}
	}
	closedir(dfd);
}

#ifndef DIRSIZ
#define DIRSIZ	14
#endif
struct direct {	/* directory entry */
	ino_t d_ino;		/* inode number */
	char	d_name[DIRSIZ];	/* long name does not have '\0' */
};

int fstat(int fd, struct stat *);

/* opendir:	open a directory for readdir calls	*/
DIR *opendir(char *dirname)
{
	int fd;
	struct stat stbuf;
	DIR *dp;

	if ((fd = open(dirname, O_RDONLY, 0)) == -1
		|| fstat(fd, &stbuf) == -1
		|| (stbuf.st_mode & S_IFMT) != S_IFDIR
		|| (dp = (DIR *) malloc(sizeof(DIR))) == NULL)
		return NULL;
	dp->fd = fd;
	return dp;
}

/* closedir: close directory opened by opendir	*/
void closedir(DIR *dp)
{
	if (dp)
	{
		close(dp->fd);
		free(dp);
	}
}


#include <sys/dir.h>

/* readdir: read directroy entries in sequence	*/
Dirent *readdir(DIR *dp)
{
	struct direct dirbuf;	/* local directory structure	*/
	static Dirent d;	/* return: portable structure	*/

	while (read(dp->fd, (char *) &dirbuf, sizeof(dirbuf))
			== sizeof(dirbuf)) {
		if (dirbuf.d_inc == 0) /* slot not in use */
			continue;
		d.ino = dirbuf.d_ino;
		strncpy(d.name, dirbuf.d_name, DIRSIZ);
		d.name[DIRSIZ] = '\0';	/* ensure termination */
		return &d;
	}
	return NULL;
}
