# simple makefile, hopefully that can be used for later projects
# set compiler
CC=g++
# set flags
DEBUG=-g
WARN=-Wall -W
STD=-std=c++11
CFLAGS=$(WARN) $(DEBUG) $(STD) -c
LFLAGS=$(WARN) $(DEBUG)
# set environment
BINDIR=../
NAME=main
EXE=$(BINDIR)$(NAME)
EXT=cpp
SRCS=$(shell find . -name "*.$(EXT)")
OBJS=$(SRCS:.cpp=.o)

.PHONY: clean

all: $(EXE)

$(EXE): $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o $@
	
.cpp.o:
	$(CC) $(CFLAGS) $<
	
clean:
	$(RM) *.o $(EXE)
