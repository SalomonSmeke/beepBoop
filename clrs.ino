/*
 * Salomon Smeke Cohen - ssmeke.io
 * clrs irl
 * 
 * This code is designed to be relatively easy to read and 
 * perform well. Not to be modular or easy to adapt.
 * 
 */

#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>

/*
 * byte MPIN
 * : Pin for neopixel matrix communication
 * byte XPPIN
 * : Pin for potentiometer X axis
 * byte YPPIN
 * : Pin for potentiometer Y axis
 * byte CYCLEBUF
 * : Buffer to reduce accidental input
 * byte CYCLETICK
 * : Buffer tick
 * float POTDEAD
 * : Desired potentiometer dead zone
 */

byte MPIN = 0;
byte XPPIN = 0;
byte YPPIN = 0;
byte CYCLEBUF = 0;
byte CYCLETICK = 0;
float POTDEAD = 511 * .3;

Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(8, 8, MPIN, 
  NEO_MATRIX_TOP + NEO_MATRIX_RIGHT +
  NEO_MATRIX_COLUMNS + NEO_MATRIX_PROGRESSIVE);

void setup()  {
  matrix.begin();
  matrix.setBrightness(64);
  matrix.show();
  pinMode(XPPIN, OUTPUT);
  pinMode(YPPIN, OUTPUT);
}

void loop()  {
  byte mask = potDir();
  if (mask == B1010 || mask == B1001 || mask == B0110 || mask == B0101) {
    mask = bufferedInput(mask, 10);
    if (mask) {
      select(mask);
    }
  }
  
  delay(10);
  //matrix.drawPixel(x, y, r);
  //matrix.show();
  //matrix.drawPixel(x, y, clr);
}

void select(byte mask) {
  
}

/*
 * bufferedInput(byte mask)
 * : Returns either mask or 0, if the input has been the same
 * : for given sensitivity.
 * : THIS USES A SHARED BUFFER.
 * : FOR SAFETY, WHENEVER THERE IS A POSITIVE MASK MATCH,
 * : THE BUFFER IS CLEARED.
 */

byte bufferedInput(byte mask, byte sensitivity){
  if (mask == CYCLEBUF) {
    if (CYCLETICK >= sensitivity) {
      CYCLETICK = 0;
      CYCLEBUF = 0;
      return mask;
    } else {
      CYCLETICK++;
    }
  } else {
    CYCLEBUF = mask;
    CYCLETICK = 0;
  }
  return 0;
}

/*
 * potDir() -
 * : Returns: bitmask byte [00][00][00][00] of potentiometer direction
 * : Unused [00] Unused [00] X [00] Y [00]
 * : [00] - No significant value
 * : [10] - Positive value
 * : [01] - Negative value
 * 
 * : Unused values might later be used to determine intensity. 
 * : 4 unused bits = 16 intensity values.
 * : Alternatively, 2 unused bits per direction = 4 directional intensities.
 * 
 * Example -
 * : Top [][][][10] + Left [][][01][] = TopLeft 00000110 (6)
 */

byte potDir(){
  short x = analogRead(XPPIN) - 512;
  short y = analogRead(YPPIN) - 512;
  byte res = 0;
  if (y - POTDEAD > 0) {
    res |= B10;
  }
  if (y + POTDEAD < 0) {
    res |= B01;
  }
  if (x - POTDEAD > 0) {
    res |= B1000;
  }
  if (x + POTDEAD < 0) {
    res |= B0100;
  }
  return res;
}

