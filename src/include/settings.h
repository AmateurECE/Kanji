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

#include "set.h"

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

extern int settings_match(const void *, const void *);
extern void settings_write(void *);
extern int settings_init(settings *, int);
extern void settings_print(void *);
extern int settings_change(settings *, char *);

/******************************************************************************/
