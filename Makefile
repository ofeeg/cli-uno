SOURCEDIR= src
TESTDIR= tests
SOURCES= $(wildcard $(SOURCEDIR)/*.c)
TESTS= $(wildcard $(TESTDIR)/*.c)
OBJECTS= $(patsubst $(SOURCEDIR)%.c,%.o,$(SOURCES))
TEST_OBJECTS= $(patsubst $(TESTDIR)%_test.c,%.o,$(TESTS))
CC=gcc

#FLAGS=

all: uno

debug: dbguno

uno: $(OBJECTS)
	$(CC) -Wall -o $@ $^ 

dbguno: $(OBJECTS)
	$(CC) -g -Wall -o $@ $^

tests: $(TEST_OBJECTS)

$(TEST_OBJECTS): %.o: $(OBJECTS)
	$(CC) -Wall $(TESTDIR)$*_test.c $^ -o $@

#$(#OBJECTS): $(#SOURCES)
#	$(#CC) -g -Wall -c -o $@ $<

clean:
	rm -f */*.o */*.c~ 
