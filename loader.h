/*
   Salomon Smeke Cohen - ssmeke.io
   loader -> beepBoop

   Proper dependency ordering loading and instance variable creation.
*/
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>
#include <wdt.h> //Dead man switch

typedef uint8_t val;

#include "RGB.h"
RGB cornerColors[2][2];

#include "config.h"
#include "matrix.h"
#include "constants.h"

val CYCLEBUF = 0; //Used to store previously read pot value
val CYCLETICK = 0; //Used to count matched pot values
val BASETICK = 0; //Used to store the base from which sensitivity is calculated.
                  //Varies for purposes of speeding up to lower input latency
                  //after an accepted buffered input.
val HOMEDEBOUNCE = 0; //Used to count time since the home button was pressed
                      //For purposes of debounce.
#include "input.h"
