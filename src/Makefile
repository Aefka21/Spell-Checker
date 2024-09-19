CC=gcc
CFLAGS=-std=c89 -ansi -Wall
INC=-I include/
 
correcteur_0: correcteur_0.c ATR.o Listes.o
	$(CC) $(INC) -o $@ $^ $(CFLAGS) 

correcteur_1: correcteur_1.c ATR.o Listes.o Levenshtein.o
	$(CC) $(INC) -o $@ $^ $(CFLAGS)

correcteur_2: correcteur_2.c ATR.o Listes.o Levenshtein.o ArbreBK.o
 
%.o : %.c
	$(CC) $(INC) -o $@ -c $< $(CFLAGS) 
 
clean:
	rm -rf $(SRC)*.o

mrproper: clean
	rm -rf correcteur_2
