/*******************************************************************************
 * NAME:	    game_operation.c
 *
 * AUTHOR:	    Ethan D. Twardy
 *
 * DESCRIPTION:	    This source code file contains all of the game-level
 *		    functions that will be called directly by main() in main.c.
 *
 * CREATED:	    06/14/2017
 *
 * LAST EDITED:	    06/14/2017
 ***/

/*******************************************************************************
 * INCLUDES
 ***/

#include "game_operation.h"

/*******************************************************************************
 * TYPE DEFINITIONS
 ***/

/* For convenience, define a wrapper type for the type unsigned int. */
typedef unsigned int ui_t;

/*******************************************************************************
 * STATIC FUNCTION PROTOTYPES
 ***/

/* Functions called by do_command: */
static int new_file(KanjiList *);
static int choose_file(KanjiList *, settings_list *);
static void game_exit(KanjiList *, settings_list *);
static void settings_menu(settings_list *);

/* Other functions: */
static void start_game();
static int get_new_kanji(KanjiList *);

/*******************************************************************************
 * API FUNCTIONS
 ***/

/*******************************************************************************
 * FUNCTION:	    do_command
 *
 * DESCRIPTION:	    Host function for all of the source code in this file. takes
 *		    an unsigned int which is used as a bit mask to determine
 *		    which command needs to be performed, then calls the function
 *		    with the right arguments.
 *
 * ARGUMENTS:	    flags: unsigned int -- bit mask for determining command.
 *
 * RETURN:	    int -- 0 on failure, -1 otherwise.
 *
 * NOTES:	    none.
 ***/
int do_command(unsigned int flags, settings_list * settings_)
{

  switch (flags) {
  case ((ui_t) NEW_FILE):
    new_file(settings_);
    break;

  case ((ui_t) CHOOSE_FILE):
    choose_file(settings_);
    break;

  case ((ui_t) HELP):
    print_help();
    break;

  case ((ui_t) SETTINGS):
    settings_menu();
    break;

  case ((ui_t) EXIT):
    game_exit();
    break;

  default:
    return -1;
  }

  return 0;
}

/*******************************************************************************
 * STATIC FUNCTIONS
 ***/

/*******************************************************************************
 * FUNCTION:	    new_file
 *
 * DESCRIPTION:	    Creates a new kanji file, and prompts the user to enter
 *		    kanji.
 *
 * ARGUMENTS:	    list: (KanjiList *) -- pointer to the current list of kanji.
 *
 * RETURN:	    int -- 0 for success, -1 otherwise.
 *
 * NOTES:	    none.
 ***/
static int new_file(KanjiList * list)
{
  char * filename = calloc(64, sizeof(char));

  printf("Please enter the name of your new file.\n");
  print_line();
  fgets(filename, 63, stdin);
  
  while (*filename == '\0' || exists(filename)) {
    print_line();
    printf("That is not an valid filename. Please enter the name of a " \
	   "legal file that does not yet exist in the directory.\n");
    print_line();
    fgets(filename, 63, stdin);
  }

  sprintf(filename, "%s.kanji", filename);
  get_new_kanji(list);

  print_line();
  printf("Writing Kanji...");
  if (kanji_write(list, filename))
    return 1;

  printf("Done.\n");

  /* INSERT THE FILE INTO SETTINGS_ ********************************************************************************/

  return 0;
}

/*******************************************************************************
 * FUNCTION:	    choose_file
 *
 * DESCRIPTION:	    Prompts the user to choose the kanji file to read from.
 *
 * ARGUMENTS:	    list: (KanjiList *) -- an empty list of kanji
 *		    settings_: (settings_list *) -- pointer to settings.
 *
 * RETURN:	    int -- 0 on success, -1 otherwise.
 *
 * NOTES:	    none.
 ***/
static int choose_file(KanjiList * list, settings_list * settings_)
{
  struct setting_t * dir = (struct setting_t *)malloc(sizeof(struct setting_t));
  struct dirent * pDirent = NULL;
  DIR * pDir = NULL;
  *dir = (struct setting_t){.name = "File Directory"};
  set_remove(settings_, (void **)&dir);
  if ((pDir = opendir(dir->data)) == NULL)
    return 0;
  
  while ((pDirent = readdir(pDir))) {

    print_line();
    printf("%s\n", pDirent->d_name);

  }

  char * filename = calloc(64, sizeof(char));
  print_line();
  printf("Please enter the name of the file you would like to use.");
  fgets(filename, 63, stdin);

  while (*filename == '\0' || !exists(filename)) {

    print_line();
    printf("That filename is not valid. Please enter another one.\n");
    fgets(filename, 63, stdin);

  }

  struct setting_t * file = (struct setting_t *)malloc(sizeof(struct setting_t));
  *file = (struct setting_t){.name = "Current File"};
  set_remove(settings_, (void **)&file);
  strncpy(file->data, filename, sizeof(file->data));
  set_insert(settings_, file);

  if (kanji_init(list, filename))
    return 1;

  return 0;
}

/*******************************************************************************
 * FUNCTION:	    game_exit
 *
 * DESCRIPTION:	    Saves all resources and exits the game.
 *
 * ARGUMENTS:	    list: (KanjiList *) -- the current list of kanji.
 *		    settings_: (settings_list *) -- pointer to the settings.
 *
 * RETURN:	    void.
 *
 * NOTES:	    
 ***/
static void game_exit(KanjiList * list, settings_list * settings_)
{
  struct setting_t * file = (struct setting_t *)malloc(sizeof(struct setting_t));
  *file = (struct setting_t){.name = "Current File"};
  if (set_remove(settings_, (void **)&file) != 0) {
    kanji_write(list, file->data);
    set_insert(settings_, file);
  }
  kanji_dest(list);
  free(settings_);
}

/*******************************************************************************
 * FUNCTION:	    settings_menu
 *
 * DESCRIPTION:	    allows the user to change any settings, if necessary.
 *
 * ARGUMENTS:	    settings_: (settings_list *) -- pointer to the settings.
 *
 * RETURN:	    void.
 *
 * NOTES:	    
 ***/
static void settings_menu(settings_list * settings_)
{
  printf("* ********* SETTINGS **********\n");
  set_traverse(settings_, print_settings);
  printf("* *****************************\n");
  printf("* Please enter any commands or changes in the form [name] " \
	 "= [value]\n* Or type exit to return to the main menu.\n");
  print_line();
  while (1) {

    char * command = calloc(256, sizeof(char));
    fgets(command, 255, stdin);
    chomp(command);
    lower_case(command);
    if (!strcmp(command, "exit"))
      break;
    else if (change_settings(settings_, command))
      printf("Unrecognized Command. Please try again.\n");
    
    print_line();
  }
  print_menu();
}

/*******************************************************************************
 * FUNCTION:	    start_game
 *
 * DESCRIPTION:	    Asks the user questions about kanji and records the answers.
 *
 * ARGUMENTS:	    
 *
 * RETURN:	    
 *
 * NOTES:	    
 ***/
static void start_game()
{

}

/*******************************************************************************
 * FUNCTION:	    get_new_kanji
 *
 * DESCRIPTION:	    Get new kanji from stdin.
 *
 * ARGUMENTS:	    
 *
 * RETURN:	    int -- 0 on success, 1 otherwise.
 *
 * NOTES:	    
 ***/
static int get_new_kanji(KanjiList * list)
{
  Kanji * kanji;
  unsigned int key;
  char * buff;

  print_line();
  printf("Please enter the kanji you would like to write to this file."  \
	 " When you are finished, please type " \
	 "'finished' in the Meaning field\n");

  /* TODO: Implement using a switch statement and a sentinel. For example--
   * int i = 0;
   * switch (i) {
   * case (0):
   *	key = strtod(buff);
   *	i++;
   *	break;
   * ...
   * }
   */

  while (1) {

    buff = calloc(32, sizeof(char));
    print_line();
    printf("Meaning: ");
    fgets(buff, 31, stdin);
    
    if (!strcmp(buff, "finished"))
      break;

    kanji = malloc(sizeof(Kanji));
    strncpy(kanji->meaning, buff, sizeof(kanji->meaning));

    print_line();
    printf("Key: ");
    fgets(buff, 32, stdin);
    key = atoi(buff);
    kanji->key = key;
    
    print_line();
    printf("Symbol: ");
    kanji->kanji = fgetwc(stdin);

    if (kanji_insert(list, kanji))
      return 1;

  }
  
  return 0;
}

/******************************************************************************/
