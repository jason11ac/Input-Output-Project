#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>


int main(int argc, char* argv[])
{
  int c;
  int fd0;
  int fd1;
  int *a = NULL; //Used for forcing seg fault
  int b;
  static int segfault = 0; //Seg fault flag
  static int catch = 0; //Catch flag

  void handler(int sig) //Seg fault handler for catch
  {
    fprintf(stderr, "Segmentation fault was caught\n");
    exit(3);
  }
  
  while (1)
    {
      static struct option long_options[] =
	{
	  {"input", required_argument, NULL, 'i'},
	  {"output", required_argument, NULL, 'o'},
	  {"segfault", no_argument, &segfault, 1},
	  {"catch", no_argument, &catch, 1},
	  {0, 0, 0, 0}
	};

      int option_index = 0;
      c = getopt_long(argc, argv, "i:o:", long_options, &option_index);

      if (optopt) //Will be non-zero when missing required argument. 
	{
	  exit(1);
	}
      
      if (c == -1)
	  break; //No arguments given
      
      switch(c)
	{
	case 'i':
	  fd0 = open(optarg, O_RDONLY); //Open input file provided
	  if (fd0 == -1)
	    {
	      perror("Error with input");
	      exit(1);
	    }
	  close(0);
	  dup(fd0);
	  break;
	case 'o':
	  fd1 = creat(optarg, S_IWUSR | S_IRUSR); //Create output file
	  if (fd1 == -1)
	    {
	      perror("Error with output");
	      exit(2);
	    }
	  close(1);
	  dup(fd1);
	  break;
	case 0: // c is 0 when flag is set. Force a seg fault or catch it
	  if (catch)
	    {
	      signal(SIGSEGV, handler);
	      b = *a;
	    }
	  break;
	default:
	  break;
	}
    }
  if (segfault) //If segfault flag set by argument
    {
      b = *a;
    }

  char buffer; //One character buffer
  
  while(read(0, &buffer, 1) > 0) //Final read and write
    {
      write(1, &buffer, 1);
    }

  exit(0);
}
	
