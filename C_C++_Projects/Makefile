CC = gcc
CFLAGS = -Wall -pedantic -std=c11 -ggdb
LIBS = -lcurl

# List of object files
OBJS = crawler.o pagedir.o hashtable.o bag.o url.o curl.o
# Name of executable
PROG = crawler
# Header files
HDRS = crawler.h pagedir.h hashtable.h bag.h url.h curl.h

# Compilation rules
$(PROG): $(OBJS)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

# Object files dependencies
crawler.o: crawler.c $(HDRS)
	$(CC) $(CFLAGS) -c crawler.c

pagedir.o: pagedir.c pagedir.h
	$(CC) $(CFLAGS) -c pagedir.c

hashtable.o: hashtable.c hashtable.h
	$(CC) $(CFLAGS) -c hashtable.c

bag.o: bag.c bag.h
	$(CC) $(CFLAGS) -c bag.c

url.o: url.c url.h
	$(CC) $(CFLAGS) -c url.c

curl.o: curl.c curl.h
	$(CC) $(CFLAGS) -c curl.c

# Cleanup rule
clean:
	rm -f *~
	rm -f *.o
	rm -f $(PROG)
