OBJS = main.o menus.o mygetch.o init.o music.o map.o share.o controls.o character.o engine.o game.o
CC = g++
DEBUG =
CFLAGS = -Wall -c -O3 $(DEBUG)
LFLAGS = -pthread -lSDL2 -lSDL2_mixer -lSDL2_ttf $(DEBUG)

mc : $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o mc

main.o : main.cpp init.h menus.h music.h character.h map.h engine.h game.h
	$(CC) $(CFLAGS) main.cpp

init.o : init.h init.cpp character.h map.h share.h engine.h
	$(CC) $(CFLAGS) init.cpp

menus.o : menus.h menus.cpp controls.h share.h engine.h init.h
	$(CC) $(CFLAGS) menus.cpp

share.o : share.h share.cpp
	$(CC) $(CFLAGS) share.cpp

controls.o : controls.h controls.cpp mygetch.h engine.h controls.h
	$(CC) $(CFLAGS) controls.cpp

character.o : character.h character.cpp share.h engine.h
	$(CC) $(CFLAGS) character.cpp

map.o : map.h map.cpp share.h
	$(CC) $(CFLAGS) map.cpp

mygetch.o : mygetch.h mygetch.cpp
	$(CC) $(CFLAGS) mygetch.cpp

music.o : music.h music.cpp
	$(CC) $(CFLAGS) music.cpp

engine.o : engine.h engine.cpp
	$(CC) $(CFLAGS) engine.cpp

game.o : game.h game.cpp map.h init.h engine.h controls.h character.h
	$(CC) $(CFLAGS) game.cpp
	

clean:
	\rm *.o mc


