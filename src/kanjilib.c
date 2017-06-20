/*******************************************************************************
 * NAME:	    kanjilib.c
 *
 * AUTHOR:	    Ethan D. Twardy
 *
 * DESCRIPTION:	    Source code containing functions adhering to the function
 *		    prototypes in kanjilib.h. These are mostly auxiliary
 *		    functions, to be used by code elsewhere.
 *
 * CREATED:	    06/14/2017
 *
 * LAST EDITED:	    06/14/2017
 ***/

/*******************************************************************************
 * INCLUDES
 ***/

#include <stdlib.h>

/*******************************************************************************
 * API FUNCTIONS
 ***/

/*******************************************************************************
 * FUNCTION:	    lower_case
 *
 * DESCRIPTION:	    Converts the string given to lower case.
 *
 * ARGUMENTS:	    str: (char *) -- the string to convert.
 *
 * RETURN:	    void.
 *
 * NOTES:	    side-effects: the value of str is changed.
 ***/
void lower_case(char * str)
{
  char * ch;
  
  for (ch = str; *ch != '\0'; ch++) {
    *ch = tolower(*ch);
  }
}

/*******************************************************************************
 * FUNCTION:	    chomp
 *
 * DESCRIPTION:	    Similar to the std function chomp() in Perl. This function
 *		    removes a terminating newline character and replaces it with
 *		    a null character, if it exists.
 *
 * ARGUMENTS:	    str: (char *) -- the string to operate on.
 *
 * RETURN:	    int -- 1 if there was a newline char replaced, 0 otherwise.
 *
 * NOTES:	    
 ***/
int chomp(char * str)
{
  char * c = str + strlen(str) - 1;
  if (*c == '\n') {
    *c = '\0';
    return 1;
  }

  return 0;
}

/*******************************************************************************
 * FUNCTION:	    exists
 *
 * DESCRIPTION:	    Checks if the file exists.
 *
 * ARGUMENTS:	    filename: (char *) -- the name of the file to check.
 *
 * RETURN:	    int -- 1 if the file does exist, 0 otherwise.
 *
 * NOTES:	    
 ***/
int exists(char * filename)
{
  FILE * fp;
  if (filename == NULL)
    return 0;

  if ((fp = fopen(filename, "r")) == NULL)
    return 0;
  
  fclose(fp);
  return 1;
}

/******************************************************************************/
