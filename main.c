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
#include "game.h"
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
  if ((list = malloc(sizeof(KanjiList))) == NULL)
    error_exit("Error: Could not allocate memory for list!");

  settings * settings_;
  if ((settings_ = malloc(sizeof(settings))) == NULL)
    error_exit("Error: Could not allocate memory for settings!");

  print_menu();
  char * command;
  while (1) {
    
    command = (char *)calloc(16, sizeof(char));
    fgets(command, 15, stdin);
    chomp(command);
    lower_case(command);
    print_line();

    if (!strcmp(command, "new file")) {
 
      if (!new_file(list))
	do_game();
      else
	printf("There was an error!\n");

    } else if (!strcmp(command, "choose file")) {

      if (!choose_file(list, settings_))
	do_game();
      else
	printf("There was an error!\n");

    } else if (!strcmp(command, "help")) {

      print_help();

    } else if (!strcmp(command, "settings")) {

      settings_menu(settings_);

    } else if (!strcmp(command, "exit")) {

      game_exit(list, settings_);
      break;

    } else
      printf("I didn't recognize that! Did you spell something wrong?\n");

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
