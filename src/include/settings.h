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

extern int settings_init(settings_list *, int);
extern int settings_destroy(settings_list *);

extern void settings_read(void *);
extern void settings_write(void *);

extern void settings_print(void *);
extern int settings_update_setting(settings_list *, char *);

extern void settings_get_setting(); /* Add parameters */
extern void settings_insert(); /* Add parameters */

/******************************************************************************/
