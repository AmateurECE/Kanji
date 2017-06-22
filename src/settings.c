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
 * FUNCTION:	    settings_init
 *
 * DESCRIPTION:	    Initializes the settings object.
 *
 * ARGUMENTS:	    settings: (settings_list *) -- the object to initialize.
 *		    default_: (bool) -- true if default settings are preferred.
 *
 * RETURN:	    int -- 0 on success, 1 otherwise.
 *
 * NOTES:	    
 ***/
int settings_init(settings_list * settings_, bool default_)
{
  set_init(settings_, settings_match, NULL);
  struct setting_t * set = NULL;
  FILE * fp = fopen(SETTINGS_FILENAME, "r");
  if (default_ || fp == NULL) {

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
 * FUNCTION:	    settings_destroy
 *
 * DESCRIPTION:	    Destroys a settings_list object and all associated memory.
 *
 * ARGUMENTS:	    settings_: (settings_list *) -- pointer to settings.
 *
 * RETURN:	    void
 *
 * NOTES:	    
 ***/
void settings_destroy(settings_list * settings_)
{


}

/*******************************************************************************
 * FUNCTION:	    settings_read
 *
 * DESCRIPTION:	    Read the settings from a file into the settings object
 *		    provided.
 *
 * ARGUMENTS:	    settings_: (settings_list *) -- the settings list.
 *		    file: (FILE *) -- pointer to the file to read from.
 *
 * RETURN:	    int -- 0 on success, -1 otherwise.
 *
 * NOTES:	    
 ***/
int settings_read(settings_list * settings_, FILE * file)
{

  return 0;

}

/*******************************************************************************
 * FUNCTION:	    settings_write
 *
 * DESCRIPTION:	    Writes the settings out to the file.
 *
 * ARGUMENTS:	    settings_: (settings_list *) -- the settings to write.
 *		    file: (FILE *) -- the file to write out to.
 *
 * RETURN:	    int -- 0 on success, -1 otherwise.
 *
 * NOTES:	    
 ***/
int settings_write(settings_list * settings_, FILE * file)
{
  FILE * fp;
  if ((fp = fopen(SETTINGS_FILENAME, "a")) == NULL)
    return;

  fwrite(setting, sizeof(struct setting_t), 1, fp);
  fclose(fp);
  return 0;
}

/*******************************************************************************
 * FUNCTION:	    settings_print
 *
 * DESCRIPTION:	    Prints the setting passed to it. This function is passed to
 *		    the traverse() function in linkedlist.c. It is declared
 *		    void (*)(void *) to be of the same signature as is required
 *		    by linkedlist.h.
 *
 * ARGUMENTS:	    setting: (void *) -- the setting to print.
 *
 * RETURN:	    void.
 *
 * NOTES:	    
 ***/
void settings_print(void *)
{
  struct setting_t * set = (struct setting_t *)setting;
  if (set->hidden == 0) {
    print_line();
    printf("%s: %s\n", set->name, set->data);
  }
}

/*******************************************************************************
 * FUNCTION:	    settings_update_setting
 *
 * DESCRIPTION:	    Parses a command and changes the necessary settings.
 *
 * ARGUMENTS:	    settings: (settings_list *) -- the settings structure.
 *		    command: (char *) -- the command to parse.
 *
 * RETURN:	    int -- 0 on success, 1 otherwise.
 *
 * NOTES:	    
 ***/
int settings_update_setting(settings_list * settings, char * command)
{

}

/*******************************************************************************
 * FUNCTION:	    settings_get_setting
 *
 * DESCRIPTION:	    Returns a setting given its name, without removing it from
 *		    the list.
 *
 * ARGUMENTS:	    settings_: (settings_list *) -- the list of settings.
 *		    name: (char *) -- the name of the setting.
 *
 * RETURN:	    int -- 0 on success, -1 otherwise.
 *
 * NOTES:	    
 ***/
int settings_get_setting(settings_list * settings_, char * name)
{


}

/*******************************************************************************
 * FUNCTION:	    settings_insert
 *
 * DESCRIPTION:	    Insert a setting into the list given its relevant data.
 *
 * ARGUMENTS:	    settings_: (settings_list *) -- the list of settings.
 *		    name: (char *) -- the name of the setting.
 *		    hidden: (bool) -- whether the setting is visible to the
 *			user or not.
 *		    data: (char *) -- a string containing relevant data for
 *			the setting object.
 *
 * RETURN:	    int -- 0 on success, -1 otherwise.
 *
 * NOTES:	    
 ***/
int setting_insert(settings_list * settings_,
		   char * name,
		   bool hidden,
		   char * data)
{


}

/******************************************************************************/
