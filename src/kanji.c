/*******************************************************************************
 * NAME:	    kanji.c
 *
 * AUTHOR:	    Ethan D. Twardy
 *
 * DESCRIPTION:	    Source code implementing the functions that are declared in
 *		    kanji.h
 *
 * CREATED:	    06/14/2017
 *
 * LAST EDITED:	    06/14/2017
 ***/

/*******************************************************************************
 * INCLUDES
 ***/

#include <wchar.h>

#include "linkedlist.h"

/*******************************************************************************
 * STATIC FUNCTION PROTOTYPES
 ***/

static void get_min_key(KanjiList *);

/*******************************************************************************
 * API FUNCTIONS
 ***/

/*******************************************************************************
 * FUNCTION:	    kanji_write
 *
 * DESCRIPTION:	    Append new kanji to the data file.
 *
 * ARGUMENTS:	    kanji: (KanjiList *) -- the list of kanji to write.
 *
 * RETURN:	    int -- 0 on success, 1 otherwise.
 *
 * NOTES:	    
 ***/
int kanji_write(KanjiList * kanji, char * filename)
{
  FILE * fp;

  if (kanji == NULL || filename == NULL || kanji_isempty(kanji))
    return 1;

  if ((fp = fopen(filename, "a")) == NULL)
    if ((fp = fopen(filename, "w")) == NULL)
      return 1;

  fwrite((void *)kanji->kanji, sizeof(Kanji), kanji->size, fp);

  fclose(fp);
  return 0;
}

/*******************************************************************************
 * FUNCTION:	    kanji_dest
 *
 * DESCRIPTION:	    Destroy the KanjiList object and all associated memory.
 *
 * ARGUMENTS:	    list: (KanjiList *) -- the list to destroy.
 *
 * RETURN:	    void.
 *
 * NOTES:	    
 ***/
void kanji_dest(KanjiList * list)
{ 
  for (int i = 0; i < list->size; i++)
    free(&(list->kanji[i]));
  
  free(list);
}

/*******************************************************************************
 * FUNCTION:	    kanji_insert
 *
 * DESCRIPTION:	    Inserts a kanji into the list.
 *
 * ARGUMENTS:	    list: (KanjiList *) -- the list to insert 'kanji' into.
 *		    kanji: (Kanji *) -- the kanji to append to 'list'.
 *
 * RETURN:	    int -- 0 on success, 1 otherwise.
 *
 * NOTES:	    
 ***/
int kanji_insert(KanjiList * list, Kanji * kanji)
{
  if (kanji == NULL || kanji->key == 0 || list == NULL)
    return 1;

  if (kanji_isempty(list)) {

    list->kanji[0] = *kanji;
    list->min_key = kanji->key;
    list->max_key = kanji->key;

  } else {

    list->kanji[kanji_hash(list, kanji)] = *kanji;
    if (kanji->key > list->max_key)
      list->max_key = kanji->key;

  }

  return 0;
}

/*******************************************************************************
 * FUNCTION:	    kanji_init
 *
 * DESCRIPTION:	    Initializes a KanjiList object by reading into it all kanji
 *		    structures contained in the file pointer fp.
 *
 * ARGUMENTS:	    kanji: (KanjiList *) -- a pointer to an uninitialized kanji
 *			   list.
 *		    filename: (char *) -- the file to read from.
 *
 * RETURN:	    int -- 0 on success, 1 on failure, 2 if there are no kanji
 *		    to read.
 *
 * NOTES:	    
 ***/
int kanji_init(KanjiList * kanji, char * filename)
{
  FILE * fp = NULL;
  Kanji * record = NULL;
  List * list = (List *)malloc(sizeof(List));

  if (kanji == NULL || filename == NULL || list == NULL)
    return 1;

  if ((fp = fopen(filename, "r")) == NULL)
    return 2;

  list_init(list, free);
  while (!feof(fp) && fread((void *)record, sizeof(Kanji), 1, fp))
    if (record != NULL)
      list_insnxt(list, list_tail(list), (void *)record);

  fclose(fp);
  kanji->size = list->size;
  kanji->kanji = calloc(kanji->size, sizeof(Kanji));
  get_min_key(kanji);

  while (!list_isempty(list)) {

    if (list_remnxt(list, NULL, (void **)&record) != 0) {
      list_dest(list);
      free(list);
      kanji_dest(kanji);
      return 1;
    }

    kanji->kanji[kanji_hash(kanji, record)] = *record;
  }

  list_dest(list);
  free(list);
  return 0;
}  

/*******************************************************************************
 * STATIC FUNCTIONS
 ***/

/*******************************************************************************
 * FUNCTION:	    get_min_key
 *
 * DESCRIPTION:	    Sets the minimum and maximum keys of the KanjiList object
 *		    provided.
 *
 * ARGUMENTS:	    list: (KanjiList *) -- the kanji list in question.
 *
 * RETURN:	    void.
 *
 * NOTES:	    none.
 ***/
static void get_min_key(KanjiList * list)
{
  ListElm * elm;
  int min = 0, max = 0;

  for (elm = list_head(list); elm != NULL; elm = list_next(elm)) {
    Kanji * k = (Kanji *)elm->data;

    if (elm == list_head(list))
      min = k->key;
    else if (k->key < min)
      min = k->key;
    else if (k->key > max)
      max = k->key;

  }

  kanji->min_key = min;
  kanji->max_key = max;
}

/******************************************************************************/
