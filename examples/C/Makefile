#
# Makefile for memspace_hmat example
#
PROGS = memspace_hmat
CFLAGS = -g -Wall -Werror -std=gnu99
LIBS = -lumf -lnuma -ltbbmalloc

all: $(PROGS)

memspace_hmat: memspace_hmat.o
	$(CC) -o $@ $(CFLAGS) $^ $(LIBS)

clean:
	$(RM) *.o a.out

clobber: clean
	$(RM) $(PROGS) memspace_hmat

.PHONY: all clean clobber
