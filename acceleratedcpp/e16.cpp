#include <iostream>
#include <string>

int main()
{
  std::cout<<"あなたの名前は？" << std::endl;
  std::string name;
  std::cin >> name;
  std::cout << "こんいちわ、" << name << "さん"
            << std::endl << "君の名前は?" << std::endl;
  std::cin >> name;
  std::cout << "どうも、" << name << "さん。"
            << "君にあえて嬉しいです" << std::endl;
  return 0;
}
