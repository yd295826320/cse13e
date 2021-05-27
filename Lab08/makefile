all: rpg
rpg: Player.o Game.o rpg.o UNIXBOARD.h
	gcc -Wall Player.o Game.o rpg.o -o rpg

Player.o: Player.c Player.h UNIXBOARD.h
	gcc -Wall -c Player.c

Game.o: Game.c Game.h UNIXBOARD.h
	gcc -Wall -c Game.c

rpg.o: Lab08_main.c UNIXBOARD.h
	gcc -Wall -c Lab08_main.c -o rpg.o
clean:
	rm -f *.o
	rm -f rpg