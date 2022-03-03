FILES := $(shell find . -type f -perm /111 | grep -vE 'sh|git')
SOURCEDIR := src
TESTDIR := tests
OBJDIR := bin
SRCS := $(wildcard $(SOURCEDIR)/*.c)
OBJS := $(patsubst $(SOURCEDIR)/%.c,%.o,$(SRCS))
TESTS := $(wildcard $(TESTDIR)/*.c)
TOBJS := $(patsubst $(TESTDIR)/%.c,$(OBJDIR)/%,$(TESTS))
CC = gcc

depend:
	makedepend -Y -fdepends --  -- $(TESTS)
uno: $(OBJS)
	$(CC) $^ main.c  -lncurses -o $@
tests: $(OBJS)
	$(shell ./compile_tests.sh)

$(OBJS): %:
	$(CC) -g -c $(SRCS) 

clean:
	rm -f *.o  */*.o */*.c~ *.c~ */*.h~ *~ $(FILES)
# DO NOT DELETE

tests/uno_test.o: headers/uno.h headers/card_game.h headers/card.h
tests/uno_test.o: headers/table.h
