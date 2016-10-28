/*
   Salomon Smeke Cohen - ssmeke.io
   RGB -> beepBoop

   helpful RGB class for color storage.
*/

class RGB
{
  public:
    RGB();
    RGB(val r, val g, val b);
    val arr[3];
    val R();
    val G();
    val B();
    void R(val c);
    void G(val c);
    void B(val c);
};

RGB::RGB(){}

RGB::RGB(val r, val g, val b) { arr[0] = r; arr[1] = g; arr[2] = b; }

val RGB::R() { return arr[0]; }

val RGB::G() { return arr[1]; }

val RGB::B() { return arr[2]; }

void RGB::R(val c) { arr[0] = c; }

void RGB::G(val c) { arr[1] = c; }

void RGB::B(val c) { arr[2] = c; }
