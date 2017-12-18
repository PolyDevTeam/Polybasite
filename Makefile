# TODO : Reworks Makefile rules with good depedency

LIBS= -I../SFML/include -L../SFML/lib -lsfml-graphics -lsfml-window -lsfml-system

CC= g++
CFLAGS= -Wall -std=c++11
EXECS= Polybasite.exe

OBJ= out/Bot.o out/BlackHole.o out/Color.o out/Basite.o out/Entity.o out/Map.o out/Game.o out/main.o

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

out/Map.o: src/Map.cpp src/Map.hpp
	@echo "*** Building Map.o ***"
	$(CC) -o $@ $(CFLAGS) -c $< $(LIBS)

out/Entity.o: src/Entity.cpp src/Entity.hpp
	@echo "*** Building Entity.o ***"
	$(CC) -o $@ $(CFLAGS) -c $< $(LIBS)

out/Color.o: src/Color.cpp src/Color.hpp
	@echo "*** Building Color.o ***"
	$(CC) -o $@ $(CFLAGS) -c $< $(LIBS)

out/Basite.o: src/Basite.cpp src/Basite.hpp
	@echo "*** Building Basite.o ***"
	$(CC) -o $@ $(CFLAGS) -c $< $(LIBS)

out/Bot.o: src/Bot.cpp src/Bot.hpp
	@echo "*** Building Bot.o ***"
	$(CC) -o $@ $(CFLAGS) -c $< $(LIBS)

out/BlackHole.o: src/BlackHole.cpp src/BlackHole.hpp
	@echo "*** Building BlackHole.cpp ***"
	$(CC) -o $@ $(CFLAGS) -c $< $(LIBS)

clean:
	@echo "*** Cleaning all .o ***"
	rm -f out/*.o
	@echo "*** Cleaning executable ***"
	rm -f $(EXECS)

mrproper:
	clean
