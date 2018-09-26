CC		= gcc
SHELL 	= /bin/sh
CFLAGS	= -g
VPATH   = src
.SUFFIXES:
.SUFFIXES: .c .o

srcdir  = src
builddir= build
executable = bigalloc

# Execute the application after compilation
#exec: \
#	$(executable)
#	./$(executable)

# Build the object into an executable
compile: $(executable).o 
	gcc -o $(executable) ./$(builddir)/$^

# Compile Source
bigalloc.o : main.c
	$(CC) -I./$(srcdir) $(CFLAGS) -c $< -o ./$(builddir)/$@
debug: 
	$(CC) -o $(executable) main.c -D_DEBUG

clean:
	rm -r $(executable) build/*

