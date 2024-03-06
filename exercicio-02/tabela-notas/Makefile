UTIL = Aluno/Aluno.c
TREE = Arvore/Arvore.c
LISTA = Lista/Lista.c
MAIN = Main.c
BINARY = executavel
NAME = tabela-notas

all:
	gcc -Wall -g $(UTIL) $(LISTA) $(TREE) $(MAIN) -o $(BINARY) -lm

run:
	./$(BINARY)

debug:
	gcc -DDEBUG -Wall $(MAIN) $(UTIL) $(LISTA) $(TREE) -o $(BINARY)

valgrind:
	valgrind --tool=memcheck --leak-check=full  --track-origins=yes --show-leak-kinds=all --show-reachable=yes ./$(BINARY)

zip:
	@zip -r $(NAME).zip *

clean:
	@rm *.o