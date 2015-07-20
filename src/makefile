CC=g++
WARN=-Wall -W -g
STD=-std=c++11
CFLAGS=$(WARN) $(STD)
MAIN=main
SRCS=main.cpp bitset.cpp

OBJS=$(SRCS:.cpp=.o)

.PHONY: clean

all: $(MAIN)

$(MAIN): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(MAIN)
	
.cpp.o:
	$(CC) $(CFLAGS) -c $< -o $@
	
clean:
	$(RM) *.o $(MAIN)
