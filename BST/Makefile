CC= g++  	

# include debugging symbols in object files,
# and enable all warnings
FLAGS= -g -Wall -std=c++11

BSTHPP= BST.hpp BSTNode.hpp BSTIterator.hpp

all: bst main

bst: testBST.o $(BSTHPP)
	$(CC) $(FLAGS) testBST.o $(BSTHPP)

main: main.o $(BSTHPP)
	$(CC) $(FLAGS) main.o $(BSTHPP)

main.o: $(BSTHPP)
	$(CC) $(FLAGS) -c main.cpp

testBST.o: testBST.cpp 
	$(CC) $(FLAGS) -c testBST.cpp

clean:
	$(RM) *.o *.gch
