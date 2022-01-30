FILES := $(shell find . -type f -perm /111 | grep -vE 'sh|git')
SOURCEDIR := src
TESTDIR := tests
OBJDIR := bin
SRCS := $(wildcard $(SOURCEDIR)/*.c)
OBJS := $(patsubst $(SOURCEDIR)/%.c,%.o,$(SRCS))
TESTS := $(wildcard $(TESTDIR)/*.c)
TOBJS := $(patsubst $(TESTDIR)/%.c,$(OBJDIR)/%,$(TESTS))
CC = gcc

uno: $(OBJS)
	$(CC) $^ main.c -o $@
tests: $(OBJS)
	$(shell ./compile_tests.sh)

$(OBJS): %: 
	$(CC)  -c $(SRCS) 

clean:
	rm -f *.o  */*.o */*.c~ *.c~ */*.h~ *~ $(FILES)
