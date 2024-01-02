CC = gcc
CFLAGS = -Wall -Wextra -pthread
OBJ_FILES = main.o util.o filemanager.o populate.o
HEADER_FILES = defs.h

query_prg: $(OBJ_FILES)
	$(CC) $(CFLAGS) $(OBJ_FILES) -o query_prg

main.o: main.c $(HEADER_FILES)
	$(CC) $(CFLAGS) -c main.c

util.o: util.c $(HEADER_FILES)
	$(CC) $(CFLAGS) -c util.c

filemanager.o: filemanager.c $(HEADER_FILES)
	$(CC) $(CFLAGS) -c filemanager.c

populate.o: populate.c $(HEADER_FILES)
	$(CC) $(CFLAGS) -c populate.c

clean:
	rm -f $(OBJ_FILES) query_prg
