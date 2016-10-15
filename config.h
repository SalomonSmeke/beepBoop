/*
   Salomon Smeke Cohen - ssmeke.io
   config -> clrsirl

   configurable variables.
*/

val M_PIN = 0; //Pin for the RGB neo pixel matrix chain
val XPOT_PIN = 0; //Pin for the X axis in the potentiometer
val YPOT_PIN = 1; //Pin for the Y axis in the potentiometer
val GRID_SIZE = 8; //NeoPixel matrix size. Assuming n*n. Multiples of 8.

float POTDEAD = 511 * .3; //Potentiometer dead zone. 30% per size default.

val MATRIXCFG = NEO_MATRIX_TOP + NEO_MATRIX_LEFT
  + NEO_MATRIX_COLUMNS + NEO_MATRIX_PROGRESSIVE;
