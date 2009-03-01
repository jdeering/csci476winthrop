# creates the API library for the game framework

LIB_NAME=libgfw.a
LIB_OBJS=GameFramework.o GFSprite.o GFText.o GFAudio.o

CPP=g++
COMPILE=-c

# the rvs flags tell ar to put named files into the library, replacing any previous versions of 
# these files if necessary, print the names of object files as it puts them into the library, and 
# add an object-file index to the library, which makes it link faster.
AR=ar
ARFLAGS=rvs

# make all/lib
all:	lib
lib:	$(LIB_NAME)

# make clean
clean:
	-rm *~ *.o

# creates the library by archiving them into the library file
$(LIB_NAME): $(LIB_OBJS)
	$(AR) $(ARFLAGS) $(LIB_NAME) $?

# creates the framework file
GameFramework.o: GameFramework.cpp GameFramework.h GFSprite.h GFText.h GFAudio.h
	$(CPP) $(CFLAGS) $(COMPILE) GameFramework.cpp

# creates the GFSprite file
GFSprite.o: GFObject.h GFSprite.cpp GFSprite.h
	$(CPP) $(CFLAGS) $(COMPILE) GFSprite.cpp

# creates the GFText object
GFText.o: GFObject.h GFText.cpp GFText.h
	$(CPP) $(CFLAGS) $(COMPILE) GFText.cpp

# creates the GFAudio object
GFAudio.o: GFObject.h GFAudio.cpp GFAudio.h
	$(CPP) $(CFLAGS) $(COMPILE) GFAudio.cpp
	
winmake: example.cpp $(LIB_OBJS)
	$(CPP) $(CFLAGS) -g -o example example.cpp $(LIB_OBJS)
