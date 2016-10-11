/*
   Salomon Smeke Cohen - ssmeke.io
   matrix -> clrsirl

   Matrix facade.
*/

Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(GRID_SIZE, GRID_SIZE, M_PIN, MATRIXCFG);

uint32_t color(byte r, byte g, byte b) { return matrix.Color(r, g, b); }

uint32_t WHITE = color(255, 255, 255);
uint32_t GRAY = color(100, 100, 100);
uint32_t BLACK = color(0, 0, 0);

uint32_t rtoc (RGB r) { return color(r.R(), r.G(), r.B()); }

void setPixel(byte x, byte y, RGB c) { matrix.drawPixel(x, y, rtoc(c)); }

void setSection(byte xoff, byte yoff, byte xlen, byte ylen, RGB c)
{
  xlen += xoff;
  ylen += yoff;
  for (byte y = yoff; y < ylen; y++)
  { for (byte x = xoff; x < xlen; x++) { setPixel(x, y, c); } }
}

void clearMatrix() { matrix.fillScreen(BLACK); }

void refresh() { matrix.show(); }
