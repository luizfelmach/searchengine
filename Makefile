FLAGS = -g -c -Wall -Iinclude
COMPILED = bin

trab3: src/main.c include/core.h include/list.h include/rbtree.h include/tst.h include/vertex.h include/util.h
	@mkdir -p $(COMPILED)
	@gcc $(FLAGS) src/main.c -o $(COMPILED)/main.o
	@gcc $(FLAGS) src/core.c -o $(COMPILED)/core.o
	@gcc $(FLAGS) src/rbtree.c -o $(COMPILED)/rbtree.o
	@gcc $(FLAGS) src/tst.c -o $(COMPILED)/tst.o
	@gcc $(FLAGS) src/list.c -o $(COMPILED)/list.o
	@gcc $(FLAGS) src/vertex.c -o $(COMPILED)/vertex.o
	@gcc $(FLAGS) src/util.c -o $(COMPILED)/util.o
	@gcc -Iinclude -o trab3 $(COMPILED)/main.o $(COMPILED)/core.o $(COMPILED)/rbtree.o $(COMPILED)/tst.o $(COMPILED)/list.o $(COMPILED)/vertex.o $(COMPILED)/util.o

clean:
	@rm -f $(COMPILED)/*.o
	@rm -rf $(COMPILED)
	@rm -f trab3

run: trab3
	@./trab3 inputs/sample1

valgrind: trab3
	@ valgrind --leak-check=full --show-leak-kinds=all ./trab3 inputs/sample1

