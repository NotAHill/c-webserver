CC = gcc
CFLAGS = -g -Wextra -pedantic -Wall -Isrc/server
LDFLAGS = -Llib
LDLIBS = -lm

SRCDIR = src
BINDIR = bin
LIBDIR = lib
OBJDIR = obj

MAIN_SRC = $(SRCDIR)/server/main.c
MAIN_OBJ = $(OBJDIR)/main.o
SERVER_OBJ = $(OBJDIR)/server.o $(OBJDIR)/client.o

all: $(BINDIR)/main

$(BINDIR)/main: $(MAIN_OBJ) $(SERVER_OBJ)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS) $(LDLIBS)

$(OBJDIR)/main.o: $(MAIN_SRC) $(SRCDIR)/server/server.h $(SRCDIR)/server/constants.h $(SRCDIR)/server/client.h
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJDIR)/server.o: $(SRCDIR)/server/server.c $(SRCDIR)/server/server.h $(SRCDIR)/server/constants.h
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJDIR)/client.o: $(SRCDIR)/server/client.c $(SRCDIR)/server/client.h $(SRCDIR)/server/constants.h
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c -o $@ $<

.PHONY: clean

clean:
	rm -rf $(OBJDIR) $(BINDIR)
