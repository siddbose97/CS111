//NAME: Siddhartha Bose
//EMAIL: siddhartha.bose@engineering.ucla.edu
//ID: 704579512


#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>
#include <signal.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <limits.h>
#include <errno.h>
#include <string.h>

void segFaultHandler(int id)
{
	fprintf(stderr, "Seg Fault Detected! \n");
	exit(4);
}

int main (int argc, char ** argv)
{

	int ifd, ofd, val, optindex, retval;
	int segfault = 0;
	const int bufferSize = 256;
	char bufferArr[bufferSize];

	static struct option long_opts[] =
	{
		{"input", required_argument, NULL, 'i'},
		{"output", required_argument, NULL, 'o'},
		{"segfault", no_argument, NULL, 's'},
		{"catch", no_argument, NULL, 'c'},
		{0,0,0,0}
	};

	while ((val=getopt_long(argc, argv, "i:o:sc", long_opts, &optindex)) != -1)
	{
		switch(val)
		{
			case 'i':
				ifd = open(optarg, O_RDONLY);

				if (ifd >= STDIN_FILENO) 
				{
					close(STDIN_FILENO);
					dup(ifd);
					close(ifd);
				} 

				//unable to open the input file
				else 
				{
					fprintf(stderr, "Error Opening Input File: %s\n", strerror(errno));
					perror("Cannot open input file!");
					exit(2);
				}
				break;
			case 'o':
				ofd = creat(optarg, 0666);
				
				if (ofd >= STDIN_FILENO) 
				{
					close(STDOUT_FILENO);
					dup(ofd);
					close(ofd);
				} 
				else
				{
					fprintf(stderr, "Error Opening Output File: %s\n", strerror(errno));
					perror("Cannot open output file!");
					exit(3);
				}
				break;
			case 'c':
				signal(SIGSEGV, segFaultHandler);
				break;
			case 's':
				segfault = 1;
				break;
			default:
				fprintf(stderr, "Unrecognized Argument while opening output file, error number: %d\n", errno );
					perror(NULL);
					exit(1);


		}
	}

	if (segfault)
	{
		char *segf = NULL;
		*segf = 'c';
	}

	while((retval = read(STDIN_FILENO, bufferArr, bufferSize)) > 0)
	{
		write(STDOUT_FILENO, bufferArr, retval);
	}

	exit(0);


}
