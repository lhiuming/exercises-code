#include <string>
#include <fstream>
#include <iostream>

#define HEIGHT 480
#define WIDTH 640
#define MAXRGB 255

using namespace std;

void write(unsigned char data[WIDTH][HEIGHT], string filename)
{
  fstream out(filename, fstream::out | fstream::binary);
  if (!out) {
    cerr << "Invalid filename: " << filename << endl;
    return;
  }

  // write ppm header
  out << "P5" << endl;
  out << "# This bitmap is generated for test. " << endl;
  out << WIDTH << ' ' << HEIGHT << endl;
  out << MAXRGB << endl;

  // write the data
  for (size_t i = 0; i < HEIGHT; ++i) {
    for (size_t j = 0; j < WIDTH; ++j)
      out << data[i][j];
  }
}

int main() {
  string fn = "test.pgm";
  unsigned char data[WIDTH][HEIGHT];
  for (size_t i = 0; i < HEIGHT; ++i)
    for (size_t j = 0; j < WIDTH; ++j)
      data[i][j] = 128;
  write(data, fn);

  return 0;
}
