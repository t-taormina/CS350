# Tyler Taormina - taormina@pdx.edu

CC = gcc
DEBUG = -g
DEFINES = 
LDFLAGS = 
CFLAGS = -Wall -Wshadow -Wunreachable-code -Wredundant-decls\
		 -Wmissing-declarations -Wold-style-definition\
		 -Wmissing-prototypes -Wdeclaration-after-statement\
		 -Wno-return-local-addr -Wuninitialized -Wextra -Wunused $(DEFINES)

OBJFILES = algos.o main.o
TARGET = a

all: $(TARGET)

$(TARGET): $(OBJFILES) 
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS)

clean cls: 
	rm -f $(PROGS) *.o *~ \#*
