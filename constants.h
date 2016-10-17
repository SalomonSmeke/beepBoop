/*
   Salomon Smeke Cohen - ssmeke.io
   constants -> clrsirl

   handy named frequent values.
*/

val pUP = B0010; //Up potentiometer
val pDN = B0001; //Down potentiometer
val pL = B0100; //Left potentiometer
val pR = B1000; //Right potentiometer

//Composite directions (corners)
val pTL = pUP | pL;
val pTR = pUP | pR;
val pBL = pDN | pL;
val pBR = pDN | pR;
