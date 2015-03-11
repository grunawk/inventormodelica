/*
  DESCRIPTION

  This file contains commonly used macros, defined-constants, structures, etc.
  This includes some convenience error-handlers as well.
*/

#ifndef _CommonPreProc_
#define _CommonPreProc_

#include <vector>

/*
 * Macros to be used to handle error return codes
 */

#define OnError(badsts, label) \
  if (badsts) goto label;

#define OnErrorState(badsts,retval,errocode,label) \
  if (badsts) {retval = errocode; goto label;}

#define OnErrorReturn(badsts, errocode) \
  if (badsts) return errocode;


/*
 * Some useful constants
 */

#define FIRST  0
#define SECOND 1
#define THIRD  2

#define XCOORD 0
#define YCOORD 1
#define ZCOORD 2

#define BEGIN  0
#define END    1

#define NOT_FOUND -1

/*
 * Some useful typedefs
 */

typedef std::vector<IUnknown *> IUnknownVec;

#endif
