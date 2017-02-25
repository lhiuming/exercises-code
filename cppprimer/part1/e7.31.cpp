// Exercies 7.31 (p279)
// using class declaration

// forward declaration
// Note:  ' class X, Y; ' fails.
class X; // optional 
class Y;

class X {
  Y *py;
}; // don't forget this ';'

class Y {
  X *px;
}; // don't forget this ';'

// let the compiler check the above definition
int main() {
  X x;
  Y y;

  return 0;
}
