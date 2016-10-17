/*
   Salomon Smeke Cohen - ssmeke.io
   loader -> clrsirl

   Proper dependency ordering loading and instance variable creation.
*/

typedef uint8_t val;

#include "RGB.h"
RGB cornerColors[2][2];

#include "config.h"
#include "matrix.h"
#include "constants.h"

val CYCLEBUF = 0;
val CYCLETICK = 0;
val BASETICK = 0;
#include "input.h"

val mode = 0;
