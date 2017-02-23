// Exercise p6.30 (p228)
// how complier treat return error
// @NOTE: this program is indtent to produce error

#include <string>
using namespace std;

bool str_subrange(const string &str1, const string &str2)
{
  if (str1.size() == str2.size())
    return str1 == str2;

  auto size = (str1.size() < str2.size())
    ? str1.size() : str2.size();

  for (decltype(size) i = 0; i != size; ++i)
    if (str1[i] != str2[i])
      return false;

  //return true;  // clang++ does detect this ommision; it prints a warnning
}

int main() {
  str_subrange("apple", "apple");
  return 0;
}
