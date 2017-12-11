# TODO : Reworks Makefile rules with good depedency

LIBS= -I../SFML/include -L../SFML/lib -lsfml-graphics -lsfml-window -lsfml-system

CC= g++
CFLAGS= -Wall -std=c++11
EXECS= Polybasite.exe

OBJ= out/Color.o out/Entity.o out/Map.o out/Game.o out/main.o

all: out/Basite.o out/Bot.o out/Color.o out/Entity.o out/Map.o out/Game.o out/main.o
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

out/Game.o: src/Game.cpp
	@echo "*** Building Game.o ***"
	$(CC) -o $@ $(CFLAGS) -c $^ $(LIBS)

out/Map.o: src/Map.cpp
	@echo "*** Building Map.o ***"
	$(CC) -o $@ $(CFLAGS) -c $^ $(LIBS)

out/Entity.o: src/Entity.cpp
	@echo "*** Building Entity.o ***"
	$(CC) -o $@ $(CFLAGS) -c $^ $(LIBS)

out/Color.o: src/Color.cpp
	@echo "*** Building Color.o ***"
	$(CC) -o $@ $(CFLAGS) -c $^ $(LIBS)

out/Basite.o: src/Basite.cpp
	@echo "*** Building Basite.o ***"
	$(CC) -o $@ $(CFLAGS) -c $^ $(LIBS)

out/Bot.o: src/Bot.cpp
	@echo "*** Building Bot.o ***"
	$(CC) -o $@ $(CFLAGS) -c $^ $(LIBS)

clean:
	@echo "*** Cleaning all .o ***"
	rm -f out/*.o
	@echo "*** Cleaning executable ***"
	rm -f $(EXECS)

mrproper:
	clean
