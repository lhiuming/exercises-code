#include <iostream>
#include <string>

using std::cin;
using std::endl;
using std::cout;
using std::string;

int main()
{
  cout << "あなたの名前を教えてください：";
  string name;
  cin >> name;

  cout << "どうのくらいのパッヂングがほし？：";
  int pad_user;
  cin >> pad_user;
  
  const string greeting = "こんいちわ、" + name + "さん！";

  const int pad_h = pad_user; // horizontal padding
  const int pad_v = 1; // vertical padding

  const int rows = pad_v * 2 + 3;
  const string::size_type cols = greeting.size() / 3 * 2 + pad_h * 2 + 2;

  cout << endl;

  // invariant: we have written r rows so far
  for (int r = 0; r != rows; ++r) {
    string::size_type c = 0;

    if (r == pad_v + 1) {
      cout << "*" << string(pad_h, ' ') << greeting
           << string(pad_h, ' ') << "*";
    } else {
      if (r == 0 || r == rows - 1) {
        cout << string(cols, '*');
      } else {
        cout << "*" << string(cols - 2, ' ') << "*";
      }
    }

    cout << endl;
  }

  return 0;
}
        
