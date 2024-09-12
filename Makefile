FLAGS = -g -c -Wall
COMPILED = bin

# all: src/main.c
# 	@ gcc -o $(FLAGS) trab3 src/*.c
# 	@gcc $(FLAGS) main.c -o $(COMPILED)/main.o


all: src/main.c include/core.h include/list.h include/rbtree.h include/tst.h
	@mkdir -p $(COMPILED)
	@gcc $(FLAGS) src/main.c -o $(COMPILED)/main.o
	@gcc $(FLAGS) src/core.c -o $(COMPILED)/core.o
	@gcc $(FLAGS) src/rbtree.c -o $(COMPILED)/rbtree.o
	@gcc $(FLAGS) src/tst.c -o $(COMPILED)/tst.o
	@gcc -o trab3 $(COMPILED)/main.o $(COMPILED)/core.o $(COMPILED)/rbtree.o $(COMPILED)/tst.o


# clean:
# 	@ rm -rf *.o trab3

clean:
	@rm -f $(COMPILED)/*.o
	@rm -rf $(COMPILED)
	@rm -f trab3

run: 
	@ ./trab3 /in/

valgrind:
	@ valgrind --leak-check=full --show-leak-kinds=all ./trab3 /in/

