/*
   Salomon Smeke Cohen - ssmeke.io
   clrs irl

   This program is designed to be relatively easy to read and
   perform well. Not to be modular or easy to adapt.
*/

#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>

/*
   byte MPIN
   : Pin for neopixel matrix communication
   byte XPPIN
   : Pin for potentiometer X axis
   byte YPPIN
   : Pin for potentiometer Y axis
   byte CYCLEBUF
   : Buffer to reduce accidental input
   byte CYCLETICK
   : Buffer tick
   float POTDEAD
   : Desired potentiometer dead zone
*/

byte MPIN = 0;
byte XPPIN = 0;
byte YPPIN = 1;
byte CYCLEBUF = 0;
byte CYCLETICK = 0;
float POTDEAD = 511 * .3;
byte tl[3] = {255, 0, 0};
byte tr[3] = {0, 255, 0};
byte bl[3] = {0, 0, 255};
byte br[3] = {10, 10 ,10};

Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(8, 8, MPIN,
                            NEO_MATRIX_TOP + NEO_MATRIX_LEFT +
                            NEO_MATRIX_COLUMNS + NEO_MATRIX_PROGRESSIVE);
//?? bytes

void setup()  {
  initMatrix();
  pinMode(XPPIN, OUTPUT);
  pinMode(YPPIN, OUTPUT);
  
}

void loop()  {
  byte mask = bufferedInput(potDir(), 10);
  if (mask == B1010 || mask == B1001 || mask == B0110 || mask == B0101) {
    select(mask);
    draw();
    refresh();
  }
  delay(10);
}

void draw() {
  byte l[8][3];
  byte r[8][3];
  interval(tl, bl, l);
  interval(tr, br, r);
  
  byte scanLine[8][3];
  for (byte y = 0; y < 8; y++) {
    interval(l[y], r[y], scanLine);
    for (byte x = 0; x < 8; x++) {
      setPixel(x, y, scanLine[x][0], scanLine[x][1], scanLine[x][2]);
    }
  }
}

void interval(byte src[3], byte tgt[3], byte intervals[8][3]){
  double factorR = stepFactor(src[0], tgt[0]);
  double factorG = stepFactor(src[1], tgt[1]);
  double factorB = stepFactor(src[2], tgt[2]);

  for (byte i = 0; i < 8; i++){
    intervals[i][0] = src[0] + (factorR * i);
    intervals[i][1] = src[1] + (factorG * i);
    intervals[i][2] = src[2] + (factorB * i);
  }
}

double stepFactor(byte src, byte tgt){
  return (double) (tgt-src) / 7.0;
}

void select(byte mask) {
  byte menuTimeOut = 255;
  byte input = 0;
  byte pos = 1;
  byte *corner;
  byte xoff = 0;
  byte yoff = 0;
  
  if (mask == B0110) {
    corner = tl;
  }
  if (mask == B1010) {
    xoff = 4;
    corner = tr;
  }
  if (mask == B0101) {
    yoff = 4;
    corner = bl;
  }
  if (mask == B1001) {
    xoff = 4;
    yoff = 4;
    corner = br;
  }
  clearMatrix();
  while (menuTimeOut) {
    input = bufferedInput(potDir(), 10);
    if (!input) {
      menuTimeOut--;
    } else {
      if (input == B0010 && (int)(*(corner + pos)) + 3 <= 255){
        *(corner + pos) += 3;
      }
      if (input == B0001 && (int)(*(corner + pos)) - 3 >= 0){
        *(corner + pos) -= 3;
      }
      if (input == B0100 && pos != 2){
        pos ++;
      }
      if (input == B0100 && pos){
        pos --;
      }
      setQuarter(xoff, yoff, *corner, *(corner + 1), *(corner + 2));
      refresh();
      menuTimeOut = 250;
    }
    delay(10);
  }
}

/*
   bufferedInput(byte mask)
   : Returns either mask or 0, if the input has been the same
   : for given sensitivity.
   : THIS USES A SHARED BUFFER.
   : FOR SAFETY, WHENEVER THERE IS A POSITIVE MASK MATCH,
   : THE BUFFER IS CLEARED.
*/

byte bufferedInput(byte mask, byte sensitivity) {
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
   potDir() -
   : Returns: bitmask byte [00][00][00][00] of potentiometer direction
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

byte potDir() {
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

void setQuarter(byte xoff, byte yoff, byte r, byte g, byte b) {
  byte xlim = xoff + 4;
  byte ylim = yoff + 4;
  for (byte i = yoff; i < ylim; i++) {
    for (byte a = xoff; a < xlim; a++) {
      setPixel(a, i, r, g, b);
    }
  }
}

//Facades for me to not have to remember junk. Slow because function calls for one liners is dumb. Sue me.

void initMatrix() {
  matrix.begin();
  matrix.fillScreen(color(20, 20, 20));
  refresh();
}

void clearMatrix() {
  matrix.fillScreen(color(0, 0, 0));
}

void setPixel(byte x, byte y, byte r, byte g, byte b) {
  matrix.drawPixel(x, y, color(r, g, b));
}

uint32_t color(byte r, byte g, byte b) {
  return matrix.Color(r, g, b);
}

void refresh() {
  matrix.show();
}

