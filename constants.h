/*
   Salomon Smeke Cohen - ssmeke.io
   constants -> clrsirl

   handy named frequent values.
*/

const val pUP = B0010; //Up potentiometer
const val pDN = B0001; //Down potentiometer
const val pL = B0100; //Left potentiometer
const val pR = B1000; //Right potentiometer

//Composite directions (corners)
const val pTL = pUP | pL;
const val pTR = pUP | pR;
const val pBL = pDN | pL;
const val pBR = pDN | pR;
