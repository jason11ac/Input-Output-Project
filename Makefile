CC = gcc
CFLAGS = -g

TARGET = MyProject

all: $(TARGET)

$(TARGET): $(TARGET).c
	$(CC) $(CFLAGS) $(TARGET).c -o $(TARGET)


check: $(TARGET) 

	printf 'Random test case data' > test.txt

	@printf '\nTest 1: No arguments, default behavior\n'
	cat test.txt | ./$(TARGET) > output1.txt
	diff test.txt output1.txt

	@printf '\nTest 2: Input and output argument\n'
	./$(TARGET) --input=test.txt --output=output2.txt
	diff test.txt output2.txt

	@printf '\nTest 3: Forcing a segmentation fault\n'
	./$(TARGET) --segfault; test $$? -eq 139 #139 is the return value of a seg fault

	@printf '\nTest 4: Catching a segmentation fault\n'
	./$(TARGET) --catch; test $$? -eq 3

	@printf '\nTest 5: Input and output arguments with catch\n'
	./$(TARGET) --input=test.txt --output=output3.txt --catch; test $$? -eq 3

	@printf '\nTest 6: Input and output arguments with segfault\n'
	./$(TARGET) --input=test.txt --output=output4.txt --segfault; test $$? -eq 139

	@printf '\nTest 7: No input file specified\n'
	./$(TARGET) --input=; test $$? -eq 1

	@printf '\nTest 8: No output file specified\n'
	./$(TARGET) --output=; test $$? -eq 2

	@printf '\nRemoving temporary testing files\n'
	@rm test.txt output1.txt output2.txt output3.txt output4.txt

	@printf '\nAll tests passed. Success!\n'

clean: $(TARGET)

	rm $(TARGET) 

dist: $(TARGET)

	tar -cvzf MyProject.tar.gz MyProject.c Makefile README.txt
