run : exe
	./exe

gdb : exe
	gdb ./exe

compileAll : driver.o myTrie.o myStack.o myRead.o traversal.o listdir.o topk_heap.o temp.o
	gcc -g -fopenmp -o exe driver.o myTrie.o myStack.o myRead.o traversal.o listdir.o topk_heap.o temp.o

driver.o : driver.c
	gcc -g -fopenmp -c driver.c

myTrie.o : myTrie.c myTrie.h
	gcc -g -fopenmp -c myTrie.c

myStack.o : myStack.c myStack.h
	gcc -g -fopenmp -c myStack.c

myRead.o : myRead.c myRead.h
	gcc -g -fopenmp -c myRead.c

traversal.o : traversal.c traversal.h myStack.h
	gcc -g -fopenmp -c traversal.c

listdir.o : listdir.c traversal.h
	gcc -g -fopenmp -c listdir.c

topk_heap.o : topk_heap.c myHeap.h myTrie.o
	gcc -g -fopenmp -c topk_heap.c

temp.o: temp.c traversal.h
	gcc -g -fopenmp -c temp.c

traverse : traversal.o listdir.o myStack.o
	gcc -g -fopenmp -o traverse_exe traversal.o listdir.o myStack.o

myStack_test.o : myStack_test.c myStack.h
	gcc -g -fopenmp -c myStack_test.c

stack_exe : myStack_test.o myStack.o
	gcc -g -fopenmp -o stack_exe myStack.c myStack_test.c

clean :
	rm *.o exe