#
# Makefile for custom_file_provider example
#
PROGS = custom_file_provider
CFLAGS = -g -Wall -Werror -std=gnu99
LIBS = -lumf -lnuma -ltbbmalloc

all: $(PROGS)

custom_file_provider: custom_file_provider.o
	$(CC) -o $@ $(CFLAGS) $^ $(LIBS)

clean:
	$(RM) *.o a.out

clobber: clean
	$(RM) $(PROGS) custom_file_provider

.PHONY: all clean clobber
