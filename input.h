/*
   Salomon Smeke Cohen - ssmeke.io
   input -> clrsirl

   input handling functionality.
*/

/*
   readDir() -
   : Returns: bitmask val [00][00][00][00] of potentiometer direction
   : Unused [00] Unused [00] X [00] Y [00]
   : [00] - No significant value
   : [10] - Positive value
   : [01] - Negative value

   : Unused values might later be used to determine intensity.
   : 4 unused bits = 16 intensity values.
   : Alternatively, 2 unused bits per direction = 4 directional intensities.

   Example -
   : Top [][][][10] + Left [][][01][] = TopLeft 00000110 (6)
*/

val readDir()
{
  short x = analogRead(XPOT_PIN) - 512;
  short y = analogRead(YPOT_PIN) - 512;
  val res = 0;
  if (y - POTDEAD > 0) { res |= B10; }
  if (y + POTDEAD < 0) { res |= B01; }
  if (x - POTDEAD > 0) { res |= B1000; }
  if (x + POTDEAD < 0) { res |= B0100; }
  return res;
}

/*
   bufferedInput(val mask)
   : Returns either mask or 0, if the input has been the same
   : for given sensitivity.
   : THIS USES A SHARED BUFFER.
   : FOR SAFETY, WHENEVER THERE IS A POSITIVE MASK MATCH,
   : THE BUFFER IS CLEARED.
*/

val bufferedInput(val mask, val sensitivity)
{
  if (mask == CYCLEBUF)
  {
    if (CYCLETICK >= sensitivity)
    {
      CYCLETICK = BASETICK;
      CYCLEBUF = 0;
      return mask;
    } else { CYCLETICK++; }
  } else
  {
    CYCLEBUF = mask;
    CYCLETICK = BASETICK;
  }
  return 0;
}

val userInput(val matches[], val matchCount, val sensitivity, val speedUp = 0)
{
  val guard = B11111111;
  val out = bufferedInput(readDir(), sensitivity);
  for (val i = 0; i < matchCount; i++) { if (out == matches[i]) { guard = 0; } }
  out &= guard;
  if (out) { BASETICK = speedUp; } else { BASETICK = 0; }
  return out;
}
