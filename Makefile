SRC = BST.c wordfreak.c
OBJ = BST.o wordfreak.o
PROG = wordfreak

$(PROG): $(OBJ)
	gcc $(OBJ) -o $(PROG)

$(OBJ): $(SRC)
