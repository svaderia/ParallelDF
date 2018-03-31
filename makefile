#### MAKEFILE ####

stack_exe : myStack_test.o myStack.o
	gcc -g -o stack_exe myStack.c myStack_test.c

myStack.o : myStack.c myStack.h
	gcc -g -c myStack.c

myStack_test.o : myStack_test.c myStack.h
	gcc -g -c myStack_test.c

mytrie.o : doc_trie.c _TRIE.h
	gcc -g -c doc_trie.c

traverse : traversal.o listdir.o myStack.o
	gcc -g -o traverse_exe traversal.o listdir.o myStack.o

traversal.o : traversal.c traversal.h myStack.h
	gcc -g -c traversal.c

listdir.o : listdir.c traversal.h
	gcc -g -c listdir.c
