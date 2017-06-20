/*******************************************************************************
 * NAME:	    game_operation.h
 *
 * AUTHOR:	    Ethan D. Twardy
 *
 * DESCRIPTION:	    Contains the typedefs and function prototypes for the source
 *		    in game_operation.c
 *
 * CREATED:	    06/14/2017
 *
 * LAST EDITED:	    06/14/2017
 ***/

/*******************************************************************************
 * API FUNCTION PROTOTYPES
 ***/

#ifndef __ET_GAME_OPERATION_H__
#define __ET_GAME_OPERATION_H__

extern void do_game();
extern int new_file(KanjiList *);
extern int choose_file(KanjiList *, settings *);
extern void game_exit(KanjiList *, settings *);
extern void settings_menu(settings *);

#endif /* __ET_GAME_OPERATION_H__ */

/******************************************************************************/
