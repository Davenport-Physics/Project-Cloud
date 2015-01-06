OBJS = main.o menus.o mygetch.o init.o music.o generation.o share.o controls.o character.o database.o
CC = g++
DEBUG = -g
CFLAGS = -Wall -c -O3 $(DEBUG)
LFLAGS = -pthread -lSDL2 -lSDL2_mixer -lsqlite3 $(DEBUG)

mc : $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o mc

main.o : main.cpp init.h menus.h music.h character.h generation.h
	$(CC) $(CFLAGS) main.cpp

init.o : init.h init.cpp character.h generation.h share.h database.h
	$(CC) $(CFLAGS) init.cpp

database.o : database.h database.cpp
	$(CC) $(CFLAGS) database.cpp

menus.o : menus.h menus.cpp controls.h mygetch.h share.h
	$(CC) $(CFLAGS) menus.cpp

share.o : share.h share.cpp
	$(CC) $(CFLAGS) share.cpp

controls.o : controls.h controls.cpp mygetch.h
	$(CC) $(CFLAGS) controls.cpp

character.o : character.h character.cpp
	$(CC) $(CFLAGS) character.cpp

generation.o : generation.h generation.cpp
	$(CC) $(CFLAGS) generation.cpp

mygetch.o : mygetch.h mygetch.cpp
	$(CC) $(CFLAGS) mygetch.cpp

music.o : music.h music.cpp
	$(CC) $(CFLAGS) music.cpp
	

clean:
	\rm *.o mc


