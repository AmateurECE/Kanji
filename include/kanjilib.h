/*******************************************************************************
 * NAME:	    kanjilib.h
 *
 * AUTHOR:	    Ethan D. Twardy
 *
 * DESCRIPTION:	    Header file containing typedefs and function prototypes for
 *		    the source in kanjilib.c
 *
 * CREATED:	    05/18/2017
 *
 * LAST EDITED:	    06/14/2017
 ***/

#ifndef __ET_KANJILIB_H__
#define __ET_KANJILIB_H__

/*******************************************************************************
 * MACRO DEFINITIONS
 ***/

#define DEFAULT_FILENAME "Heisig.kanji"
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
  "* Exit - Exit the kanjilib. Type this at any time to leave.\n"		\
  "* *****************************\n"					\
  "* "

#define print_line() (printf("* "))
#define print_menu() (printf(MENU))
#define print_help() (printf(HELP))

/*******************************************************************************
 * API FUNCTION PROTOTYPES
 ***/

extern void lower_case(char *);
extern int chomp(char *);
extern int exists(char *);

#endif /* __ET_KANJILIB_H__ */

/******************************************************************************/
