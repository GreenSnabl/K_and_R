/*	In the UNIX operating system all I/O is done by reading and writing files.
 *
 *	Before I/O a file the system must be informed of that intention.
 *
 *		"opening" the file
 *
 *	The system checks the permission, if the file exists and returns an integer (FILE DESCRIPTOR)
 *	if everything is fine.
 *
 *	Whenever I/O is to be done to that file the FILE DESCRIPTOR is used instead of the name to
 *	identify the file.
 *
 *	file descriptor is analogous to the file pointer of stdlib or file handler of MS-DOS
 *
 *	
 *	Since Keyboard input and Monitor output are so common, there are special arrangements made
 *
 *	when a shell runs a programm 3 files are opened
 *
 *		1 - standard input
 *		2 - standard output
 *		3 - standard error
 *
 *	The I/O can be redirected with < and > like
 *
 *	./prog < infile.txt  > outfile.txt
 *
 */
