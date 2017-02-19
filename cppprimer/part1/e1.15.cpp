// Exercise 1.15 (p14)
// write programs that contain some common errors discussed in page 16

#include <iostream>

int integer_function(int);

//int main ( {
int main () {

  // std::cout << "how is me." << std::endl:
  std::cout << "how is me." << std::endl;

  //std::cout << "how if i miss the quates"  std::endl;
  std::cout << "how if i miss the quates" << std::endl;


  //std::cout << "how is i left the output operator" std::endl;
  std::cout << "how is i left the output operator" << std::endl;

  //std::cout << integer_function("a") << std::endl;
  std::cout << integer_function('a') << std::endl;

  //cout << "no such function error" << std::edl;
  std::cout << "no such function error" << std::endl;

  return 0;
}

int integer_function(int v)
{
  return v + 1;
}
