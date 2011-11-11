CC = gcc
CFLAGS = -Wall -g 
OBJ = ph.o tree.o dict.o wlist.o table.o dicttree.o
DICTTREE_TEST_OBJ = dicttree_test.o dicttree.o dict.o wlist.o tree.o table.o

ph: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o ph -lm

dt_test: $(DICTTREE_TEST_OBJ)
	$(CC) $(CFLAGS) $(DICTTREE_TEST_OBJ) -o dt_test

clean:
	rm -f *.o
	rm -f dt_test
	rm -f ph
dict.o: dict.h
dicttree.o: dicttree.h dict.h
dicttree_test.o: dicttree.h dict.h
ph.o: tree.h dict.h wlist.h dicttree.h
tree.o: tree.h table.h
wlist.o: wlist.h tree.h dicttree.h

