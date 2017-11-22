LIBS= -I../SFML/include -L../SFML/lib -lsfml-graphics -lsfml-window -lsfml-system

CC= g++
CFLAGS= -Wall
EXECS= Polybasite

OBJ= out/main.o

all: out/main.o
	@echo "*** Building the game ***"
	$(CC) -o $(EXECS) $^ $(CFLAGS) $(LIBS)

release: clean
release: CFLAGS += -O3
release: all

debug: clean
debug: CFLAGS += -g -DDEBUG
debug: all

out/main.o: src/main.cpp
	@echo "*** Building main.o ***"
	$(CC) -o $@ $(CFLAGS) -c $^ $(LIBS)

clean:
	@echo "*** Cleaning all .o ***"
	rm out/*.o
	@echo "*** Cleaning executable ***"
	rm $(EXECS)

mrproper:
	clean
