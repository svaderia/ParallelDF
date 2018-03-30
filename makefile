#### MAKEFILE ####


stack_exe : myStack_test.o myStack.o
	gcc -o stack_exe myStack.c myStack_test.c

myStack.o : myStack.c myStack.h
	gcc -c myStack.c

myStack_test.o : myStack_test.c myStack.h
	gcc -c myStack_test.c