/*******************************************************************************
 * NAME:	    main.c
 *
 * AUTHOR:	    Ethan D. Twardy
 *
 * DESCRIPTION:	    A game, that tests the user's knowledge of kanji.
 *		    Shows them the kanji, then asks them to name its meaning.
 *		    Alternatively, also gives the kanji's meaning and asks the
 *		    user to draw it, then to check their answer. All kanji
 *		    meanings are based upon the Heisig method.
 *
 * CREATED:	    05/17/17
 *
 * LAST EDITED:	    05/17/17
 */

/*******************************************************************************
 * INCLUDES
 ***/

#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <locale.h>
#include <dirent.h>

#include "kanji.h"
#include "kanjilib.h"
#include "game_operation.h"

/*******************************************************************************
 * LOCAL FUNCTION PROTOTYPES
 ***/

static inline void error_exit(char *);

/*******************************************************************************
 * MAIN
 ***/

int main(int argc, char * argv[])
{
  setlocale(LC_ALL, "");

  KanjiList * list;
  settings * settings_;
  unsigned int flags = 0x0;
  char * command;

  print_menu();
  while (1) {

    /* There's no reason why there should ever be a command
     * more than 15 chars long. */
    command = (char *)calloc(16, sizeof(char));
    fgets(command, 15, stdin);
    chomp(command);
    lower_case(command);
    print_line();

    if (!strcmp(command, "new file"))		flags |= NEW_FILE;
    else if (!strcmp(command, "choose file"))	flags |= CHOOSE_FILE;
    else if (!strcmp(command, "help"))		flags |= HELP;
    else if (!strcmp(command, "settings"))	flags |= SETTINGS;
    else if (!strcmp(command, "exit"))		flags |= EXIT;
    else
      printf("I didn't recognize that! Did you spell something wrong?\n");

    if (flags)
      do_command(flags);
    /* TODO: Implement a way using the flags bit mask to safely exit from the
     * program and save all resources. */

    free(command);
    print_line();
  }
  
  printf("\n");
  return 0;
}

/*******************************************************************************
 * LOCAL FUNCTIONS
 ***/

/*******************************************************************************
 * FUNCTION:	    error_exit
 *
 * DESCRIPTION:	    Allows the program to exit immediately if an error occurs.
 *
 * ARGUMENTS:	    msg: (char *) -- printed to stderr.
 *
 * RETURN:	    void.
 *
 * NOTES:	    No return.
 ***/
static inline void error_exit(char * msg)
{
  fprintf(stderr, "%s\n", msg);
  exit(1);
}

/******************************************************************************/
