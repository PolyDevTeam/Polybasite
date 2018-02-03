LIBS= -I../../../../../SFML/include -L../../../../../SFML/lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-network

CC= g++
CFLAGS= -Wall -std=c++11
EXECS= Polybasite.exe
OBJ= out/Game.o out/main.o


all: $(OBJ)

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
	$(CC) -o $@ $(CFLAGS) -c $< $(LIBS)

out/Game.o: src/Game.cpp src/Game.hpp
	@echo "*** Building Game.o ***"
	$(CC) -o $@ $(CFLAGS) -c $< $(LIBS)


clean:
	@echo "*** Cleaning all .o ***"
	rm -f out/*.o
	@echo "*** Cleaning executable ***"
	rm -f $(EXECS)

mrproper:
	clean
