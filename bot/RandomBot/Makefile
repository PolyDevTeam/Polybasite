LIBS= -lsfml-window -lsfml-system -lsfml-network

CC= g++
CFLAGS= -Wall -std=c++11
EXECS= RandomBot.exe
OBJ= socket.o main.o

all: $(OBJ)
	@echo "*** Building RandomBot ***"
	$(CC) -o $(EXECS) $^ $(CFLAGS) $(LIBS)

release: clean
release: CFLAGS += -O3
release: all

debug: clean
debug: CFLAGS += -g -DDEBUG
debug: all

main.o: main.cpp
	@echo "*** Building main.o ***"
	$(CC) -o $@ $(CFLAGS) -c $< $(LIBS)

socket.o: ../../src/Socket.cpp ../../src/Socket.hpp
	@echo "*** Building Socket.o ***"
	$(CC) -o $@ $(CFLAGS) -c $< $(LIBS)

clean:
	@echo "*** Cleaning all .o ***"
	rm -f *.o
	@echo "*** Cleaning executable ***"
	rm -f $(EXECS)

mrproper:
	clean
