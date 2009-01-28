# creates the Wordplay game for the CSCI476 framework

GAME_NAME=Wordplay
GAME_OBJS=Dictionary.o Board.o Tile.o lib.functions.o

CPP=g++
COMPILE=-c
LINKOBJ=-o

# make all
all:	game

# make clean
clean:
	-rm *~ *.o

# creates the game
game: $(GAME_OBJS)
	$(CPP) $(CFLAGS) $(LINKOBJ) $(GAME_NAME) $(GAME_OBJS)

# creates the Dictionary file
Dictionary.o: Dictionary.cpp Dictionary.h
	$(CPP) $(CFLAGS) $(COMPILE) Dictionary.cpp

# creates the Board file
Board.o: Board.cpp Board.h
	$(CPP) $(CFLAGS) $(COMPILE) Board.cpp

# creates the Tile file
Tile.o: Tile.cpp Tile.h
	$(CPP) $(CFLAGS) $(COMPILE) Tile.cpp

# creates the function library
lib.functions.o: lib.functions.cpp Tile.h
	$(CPP) $(CFLAGS) $(COMPILE) lib.functions.cpp
