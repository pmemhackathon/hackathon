#
# Makefile for memspace_numa example
#
PROGS = memspace_numa
CFLAGS = -g -Wall -Werror -std=gnu99
LIBS = -lumf -lnuma -ltbbmalloc

all: $(PROGS)

memspace_numa: memspace_numa.o
	$(CC) -o $@ $(CFLAGS) $^ $(LIBS)

clean:
	$(RM) *.o a.out

clobber: clean
	$(RM) $(PROGS) memspace_numa

.PHONY: all clean clobber
