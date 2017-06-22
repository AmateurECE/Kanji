/*******************************************************************************
 * NAME:	    settings.h
 *
 * AUTHOR:	    Ethan D. Twardy
 *
 * DESCRIPTION:	    Header file detailing implementation of interface for using
 *		    settings objects.
 *
 * CREATED:	    06/20/2017
 *
 * LAST EDITED:	    06/20/2017
 ***/

/*******************************************************************************
 * INCLUDES
 ***/

#include <stdbool.h>

#include "linkedlist.h"

/*******************************************************************************
 * TYPE DEFINITIONS
 ***/

typedef struct _setting_ {

  char data[256];
  int hidden : 1;
  char name[63];

} setting_t;

typedef List settings_list;

/*******************************************************************************
 * API FUNCTION PROTOTYPES
 ***/

extern int settings_init(settings_list *, bool);
extern void settings_destroy(settings_list *);

extern int settings_read(settings_list *, FILE *);
extern int settings_write(settings_list *, FILE *);

extern void settings_print(void *);
extern int settings_update_setting(settings_list *, char *);

extern int settings_get_setting(settings_list *, char *);
extern int settings_insert(settings_list *, char *, bool, char *);

/******************************************************************************/
