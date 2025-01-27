#
#  Makefile
#  Projet!reseaux
#
# Created by David Lamoot on 10/01/2025.

# Executable names
EXEC1=serveur
EXEC2=client

# Compiler to use
CC=gcc

# Flags for compilation
CFLAGS=-g

# Default target
all: $(EXEC1) $(EXEC2)

# Rule for building serveur
$(EXEC1): serveur.c
	$(CC) $(CFLAGS) serveur.c -o $(EXEC1)

# Rule for building client
$(EXEC2): client.c
	$(CC) $(CFLAGS) client.c -o $(EXEC2)

# Clean up the compiled files and any temporary files
clean:
	rm -f *.o *~ $(EXEC1) $(EXEC2)

# Rule for a deep clean (removes executables in addition to temporary files)
mrproper: clean
	rm -f $(EXEC1)
	rm -f $(EXEC2)

# Phony targets
.PHONY: all clean mrproper
