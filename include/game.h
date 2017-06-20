/*******************************************************************************
 * NAME:	    game.h
 *
 * AUTHOR:	    Ethan D. Twardy
 *
 * DESCRIPTION:	    Header file containing typedefs and function prototypes for
 *		    the source in game.c
 *
 * CREATED:	    05/18/2017
 *
 * LAST EDITED:	    06/14/2017
 ***/

#ifndef __ET_GAME_H__
#define __ET_GAME_H__

/*******************************************************************************
 * INCLUDES
 ***/

#include "set.h"

/*******************************************************************************
 * MACRO DEFINITIONS
 ***/

#define DEFAULT_FILENAME "Heisig's.kanji"
#define SETTINGS_FILENAME "kanji.settings"
#define DEFAULT_SETTINGS 1
#define MENU "\n"							\
  "* *********************************************************** *\n"	\
  "* ********* KANJI: A GAME OF CHARACTER MEMORIZATION ********* *\n"	\
  "* *********************************************************** *\n"	\
  "* Written By: Ethan D. Twardy\n"					\
  "*\n"									\
  "* ********* MAIN MENU *********\n"					\
  "* New File\n"							\
  "* Choose File\n"							\
  "* Help\n"								\
  "* Settings\n"							\
  "* Exit\n"								\
  "* *****************************\n"					\
  "* "
#define HELP ""								\
  "* *********** HELP ************\n"					\
  "* New File - Create a new Kanji Character File to test your knowledge.\n" \
  "* Choose File - Choose an exisiting Character File to use.\n"	\
  "* Help - Print this menu.\n"						\
  "* Settings - Change user settings; home directory, etc.\n"		\
  "* Exit - Exit the game. Type this at any time to leave.\n"		\
  "* *****************************\n"					\
  "* "

#define print_line() (printf("* "))
#define print_menu() (printf(MENU))
#define print_help() (printf(HELP))

/*******************************************************************************
 * TYPE DEFINITIONS
 ***/

struct setting_t {

  char data[256];
  int hidden : 1;
  char name[63];

};

typedef Set settings;

/*******************************************************************************
 * API FUNCTION PROTOTYPES
 ***/

extern void lower_case(char *);
extern int chomp(char *);
extern int exists(char *);

/* ****** INTERFACING WITH SETTINGS OBJECTS ****** */

extern int settings_match(const void *, const void *);
extern void settings_write(void *);
extern int settings_init(settings *, int);
extern void print_settings(void *);
extern int change_settings(settings *, char *);

#endif /* __ET_GAME_H__ */

/******************************************************************************/
