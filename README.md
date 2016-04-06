# Input-Output-Project
A relatively simple input/output program written in C code on a Linux Server

~~~~~~~~~~~
README.txt
~~~~~~~~~~~

This tarball cantains 3 items:

     1. The C code for the project in a file called I/Oproject.c.
     2. The Makefile that can be used to make the executable for 
	      I/Oproject.c, check the executable using a number of tests as a 
	      "smoke-test", clean/delete all makefile created files, and finally 
    	  build the tarball containing these three items.
		        - The smoke-test run by inputing the command make check
		          includes 8 different tests. If all tests are successful
		          the command should output "All tests passed. Success!"
		          upon finishing. This check creates five debugging files:
		          test.txt, output1.txt, output2.txt, output3.txt and
		          output4.txt, which are all deleted at the conclusion of
		          the smoke-test. 
     3. This README text file, which describes what everything in the
        final tarball is.

The executable created by the Makefile, I/Oproject, can be used with arguments:

     --input=filename: Use the specified file as standard input.
     		               If the input file can not be opened, report a
		                   failure and return with a value of 1.
     --output=filename: Create the specified file and use it as standard
                        output. If the output file can not be created,
			                  report the failure and exit with a return code of
			                  2. 
     --segfault: Force a segmentation fault by setting a character pointer
                 to NULL and then storing through it. 
     --catch: Use signal to register a SIGSEGV handler that catches the
              segmentation fault, logs an error message and exit with a
	            return code of 3. 

     The executable can be used with any combination of the above four
     argument types. The --input and --output options require an argument
     while --segfault and --catch do not. 
