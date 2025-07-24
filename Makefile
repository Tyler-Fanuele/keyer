all: test.cxx morseBinaryTree.cxx
	g++ -o test test.cxx morseBinaryTree.cxx

clean:
	rm *.o test -f