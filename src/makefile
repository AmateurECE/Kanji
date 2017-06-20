######################################################################
# NAME: Makefile
# TARGET: Kanji -- The Kanji Memorization Game
# AUTHOR: Ethan D. Twardy
# CREATED: 
# LAST EDITED: 06/01/17
######################################################################

P=kanji
OBJECTS = ./*.c
CFLAGS = -Wall -O3 -I ./include/
LDLIBS=
CC=gcc
CFLAGS_DEBUG = -g -O0 -Wall

$(P):
	$(CC) $(CFLAGS) -o $(P) $(OBJECTS)

################################################################################
# AUXILIARY RULES
###

.PHONY: clean debug

debug:
	$(CC) $(CFLAGS_DEBUG) -o $(P) $(OBJECTS)

clean:
	rm -rf ./include/*.h~
	rm -rf ./*.c~
	rm -rf ./include/*.h~
	rm -rf ./makefile~

################################################################################
