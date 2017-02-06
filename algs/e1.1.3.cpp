#include <iostream>
#include <string>

int main(int argc, char* argv[])
{
  if (argc < 4) {
    std::cout << "Hey, not enough numbers!" << std::endl;
  } else {
    int a = std::stoi(argv[1]);
    for (int i = 2; i < 4; ++i)
      if (a != std::stoi(argv[i])) {
        std::cout << "Not Equal!" << std::endl;
        return 0;
      }
    std::cout << "All Equal!" << std::endl;
  }
  return 0;
}
