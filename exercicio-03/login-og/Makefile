ITEM = Student/Student.c
MAIN = Main.c
UTIL = Util/Util.c
HASHTABLE = Hashtable/Hashtable.c
BINARY = Main
NAME = conta_bancaria

all:
	gcc -Wall -lm -g $(ITEM) $(HASHTABLE) $(UTIL) $(MAIN) -L. -o $(BINARY) 

run:
	./$(BINARY)

valgrind:
	valgrind --tool=memcheck --leak-check=full  --track-origins=yes --show-leak-kinds=all --show-reachable=yes ./$(BINARY)

zip:
	@zip -r $(NAME).zip *

clean:
	@rm *.o

objlib:
	gcc -Wall -pedantic -Werror -Wextra -c -fPIC $(UTIL) $(ITEM)

lib:
	ar -rcs lib_util.a *.o