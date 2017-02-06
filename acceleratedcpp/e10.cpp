// framed gretting

#include <iostream>
#include <string>

int main()
{
  std::cout<<"あなたのご名前を入力しでください：";
  std::string name;
  std::cin >> name;

  // build the message
  const std::string greeting = "　こんいちわ、" + name + "さん。　";

  // buid the frank
  const std::string spaces(greeting.size() / 3 * 2, ' ');
  const std::string frank = "*" + spaces + "*";

  // build the line
  const std::string line(frank.size(), '*');

  //write out
  std::cout<<std::endl;
  std::cout<<line<<std::endl;
  std::cout<<frank<<std::endl;
  std::cout<<"*"<<greeting<<"*"<<std::endl;
  std::cout<<frank<<std::endl;
  std::cout<<line<<std::endl;

  return 0;
}
