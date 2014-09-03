CC=g++
CCFLAGS=-O2
RM=rm -f

SimpleLinkedList_test: SimpleLinkedList_test.cc SimpleLinkedList.hh TestUtils.hh
	$(CC) $(CCFLAGS) SimpleLinkedList_test.cc -o SimpleLinkedList_test

clean:
	$(RM) SimpleLinkedList_test
