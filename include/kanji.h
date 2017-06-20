/*******************************************************************************
 * NAME:	    kanji.h
 *
 * AUTHOR:	    Ethan D. Twardy
 *
 * DESCRIPTION:	    Header file containing the prototypes for source code in
 *		    kanji.c.
 *
 * CREATED:	    05/17/2017
 *
 * LAST EDITED:	    06/14/2017
 ***/

/* NOTE: I plan to go through this again as soon as I */
/* have finished implementing a hash map, and make    */
/* everything prettier. Just a heads up.              */

#ifndef __ET_KANJI_H__
#define __ET_KANJI_H__

/*******************************************************************************
 * MACRO DEFINITIONS
 ***/

#define get_key(kanji) ((kanji)->key)
#define get_char(kanji) ((kanji)->kanji)
#define get_meaning(kanji) ((kanji)->meaning)

#define kanji_size(list) ((list)->size)
#define kanji_isempty(list) (kanji_size(list) == 0 ? 1 : 0)

/* The Hash function. */
#define kanji_hash(list, kanji) ((kanji)->key - (list)->min_key)

/*******************************************************************************
 * TYPE DEFINITIONS
 ***/

typedef struct _Kanji_ {

  unsigned int key;
  wchar_t kanji;
  char meaning[32];

} Kanji;

typedef struct _KanjiList_ {

  int min_key;
  int max_key;
  int size;
  Kanji * kanji;

} KanjiList;

/*******************************************************************************
 * API FUNCTION PROTOTYPES
 ***/

extern int kanji_write(KanjiList *, char *);
extern void kanji_dest(KanjiList *);
extern int kanji_insert(KanjiList *, Kanji *);
extern int kanji_get(KanjiList *, unsigned int, Kanji **);
extern int kanji_init(KanjiList *, char *);

#endif /* __ET_KANJI_H__ */

/******************************************************************************/
