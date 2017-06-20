/*******************************************************************************
 * NAME:	    settings.c
 *
 * AUTHOR:	    Ethan D. Twardy
 *
 * DESCRIPTION:	    Source file containing the implementation of the interface
 *		    for settings objects, described in src.h
 *
 * CREATED:	    06/20/2017
 *
 * LAST EDITED:	    06/20/2017
 ***/

/*******************************************************************************
 * INCLUDES
 ***/

#include <dirent.h>
#include <unistd.h>

#include "settings.h"

/*******************************************************************************
 * API FUNCTIONS
 ***/

/*******************************************************************************
 * FUNCTION:	    settings_match
 *
 * DESCRIPTION:	    Required for set.h. This function determines if 'one' and
 *		    'two' are equal.
 *
 * ARGUMENTS:	    one: (const void *) -- parameter one.
 *		    two: (const void *) -- parameter two.
 *
 * RETURN:	    int -- 1 if they are the same, 0 otherwise.
 *
 * NOTES:	    
 ***/
int settings_match(const void * one, const void *  two)
{
  int ret = strcmp((const char *)((struct setting_t *)one)->name,
		   (const char *)((struct setting_t *)two)->name);
  if (ret == 0)
    return 1;
  else
    return 0;
}

/*******************************************************************************
 * FUNCTION:	    settings_write
 *
 * DESCRIPTION:	    Writes the settings out to the file.
 *
 * ARGUMENTS:	    setting: (void *) -- the setting to write.
 *
 * RETURN:	    void.
 *
 * NOTES:	    
 ***/
void settings_write(void * setting)
{
  FILE * fp;
  if ((fp = fopen(SETTINGS_FILENAME, "a")) == NULL)
    return;

  fwrite(setting, sizeof(struct setting_t), 1, fp);
  fclose(fp);
}

/*******************************************************************************
 * FUNCTION:	    settings_init
 *
 * DESCRIPTION:	    Initializes the settings object.
 *
 * ARGUMENTS:	    settings: (settings *) -- the object to initialize.
 *
 * RETURN:	    int -- 0 on success, 1 otherwise.
 *
 * NOTES:	    
 ***/
int settings_init(settings * settings_, int normal)
{
  set_init(settings_, settings_match, NULL);
  struct setting_t * set = NULL;
  FILE * fp = fopen(SETTINGS_FILENAME, "r");
  if (normal || fp == NULL) {

    if ((fp = fopen(SETTINGS_FILENAME, "w")) == NULL)
      return 1;

    fclose(fp);

    set = malloc(sizeof(struct setting_t));
    char * path = calloc(1024, sizeof(char));
    getcwd(path, sizeof(path));
    sprintf("%s/files", path);
    *set = (struct setting_t) {.hidden = 0, .name = "File Directory"};
    strncpy(set->data, path, sizeof(*path));
    set_insert(settings_, (void *)set);

    set = malloc(sizeof(struct setting_t));
    *set = (struct setting_t) {.hidden = 1, .name = "Current File"};
    set_insert(settings_, (void *)set);

  } else {
    while (!feof(fp)) {

      if (fread(set, sizeof(struct setting_t), 1, fp))
	set_insert(settings_, (void *)set);
      else
	goto error_exception;

    }
  }

  if (fp != NULL)
    fclose(fp);
  return 0;

 error_exception: {
    if (fp != NULL)
      fclose(fp);
    return 1;
  }
}

/*******************************************************************************
 * FUNCTION:	    print_settings
 *
 * DESCRIPTION:	    Prints the setting passed to it.
 *
 * ARGUMENTS:	    setting: (void *) -- the setting to print.
 *
 * RETURN:	    void.
 *
 * NOTES:	    
 ***/
void settings_print(void * setting)
{
  struct setting_t * set = (struct setting_t *)setting;
  if (set->hidden == 0) {
    print_line();
    printf("%s: %s\n", set->name, set->data);
  }
}

/*******************************************************************************
 * FUNCTION:	    change_settings
 *
 * DESCRIPTION:	    Parses a command and changes the necessary settings.
 *
 * ARGUMENTS:	    settings: (settings *) -- the settings structure to change.
 *		    command: (char *) -- the command to parse.
 *
 * RETURN:	    int -- 0 on success, 1 otherwise.
 *
 * NOTES:	    
 ***/
int settings_change(settings * settings, char * command)
{

}

/******************************************************************************/
