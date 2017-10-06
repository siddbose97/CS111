#NAME: Siddhartha Bose
#EMAIL: siddhartha.bose@engineering.ucla.edu
#ID: 704579512

CC = gcc
CFLAGS = -g -Wall

all: lab0

lab0: lab0.o
        $(CC) $(CFLAGS) -o lab0 lab0.o

lab0.o: lab0.c
        $(CC) -c lab0.c

check:
        @echo "Test #1: --input"
        @echo "Testing testing" > input.txt
        @echo "Using File called input.txt for testing, and running exe with --input"
        @./lab0 --input=input.txt
        @echo "########################################################################################"
        @echo "Test #2: --input and --output"
        @echo "Reusing input.txt from Test#1, outputting to the created file output.txt"
        @echo "Creating output.txt for --output"
        @./lab0 --input=input.txt --output=output.txt
        @echo "########################################################################################"
        @echo "Test #3: Diff - should return nothing or error if different (checking for proper copying)"
        @diff input.txt output.txt > /dev/null || (echo "Not correctly copied")
        @echo "########################################################################################"
        @rm -rf input.txt output.txt
        @echo "Test #4: --segfault and --catch"
        @echo "Running executable with both --segfault and --catch flags"
        @echo "If it works, will display caught message and exit with RC 4"
        @./lab0 --segfault --catch 2>&1 || [ $$? -eq 4 ]

clean:
        rm -f *.o lab0 *.txt *.tar.gz

dist:
        rm -rf lab0-704579512.tar.gz
        tar -cvzf lab0-704579512.tar.gz *.c *.png README Makefile