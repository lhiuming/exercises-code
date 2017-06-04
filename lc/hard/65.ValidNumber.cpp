/*
 * "
 * Validate if a given string is numeric.
 *
 * Some examples:
 * "0" => true
 * " 0.1 " => true
 * "abc" => false
 * "1 a" => false
 * "2e10" => true
 *
 * Note: It is intended for the problem statement to be ambiguous. You should
 * gather all requirements up front before implementing one.
 * "
 *
 * https://leetcode.com/problems/valid-number/
 *
 * My comment: A LOT astonishing valid cases! Including:
 *   [Easy  :] "2.", "3e09"
 *   [Tricky:] "-000e-00"
 *   [WTF   :] "2.e3"
 */

#include <iostream>
#include <cctype>
#include <string>

using namespace std;

class Solution {

    // FSM variables
    enum State {
      Start = 0, PreESign, PostESign, HDot, TDot, PreDigit,
      InDigit, PostDigit, E, FAIL, PASS
    };
    enum Input { _Digit = 0, _Dot, _Sign, _E, _Others, _End };

    // Setup the FSM
    //            Inputs:   _Digit     _Dot  _Sign     _E    _Others _End
    int S_Start[6]     = { PreDigit,  HDot, PreESign,  FAIL, FAIL,   FAIL };
    int S_PreESign[6]  = { PreDigit,  HDot, FAIL,      FAIL, FAIL,   FAIL };
    int S_PostESign[6] = { PostDigit, FAIL, FAIL,      FAIL, FAIL,   FAIL };
    int S_HDot[6]      = { InDigit,   FAIL, FAIL,      FAIL, FAIL,   FAIL };
    int S_TDot[6]      = { InDigit,   FAIL, FAIL,      E   , FAIL,   PASS };
    int S_PreDigit[6]  = { PreDigit,  TDot, FAIL,      E,    FAIL,   PASS };
    int S_InDigit[6]   = { InDigit,   FAIL, FAIL,      E,    FAIL,   PASS };
    int S_PostDigit[6] = { PostDigit, FAIL, FAIL,      FAIL, FAIL,   PASS };
    int S_E[6]         = { PostDigit, FAIL, PostESign, FAIL, FAIL,   FAIL };
    int* FSM[9] = {
      S_Start, S_PreESign, S_PostESign, S_HDot, S_TDot,
      S_PreDigit, S_InDigit, S_PostDigit, S_E};

public:
    bool isNumber(string s) {
        // Trim spaces
        int beg = 0, end = s.size();
        while (s[beg] == ' ') ++beg;
        while (s[end-1] == ' ') --end;
        if (end <= beg) return false;

        // Run the FSM
        int state = Start;
        while (beg < end) {
            state = FSM[state][get_input(s[beg++])]; // update
            if (state == FAIL) return false;
        }
        state = FSM[state][_End];

        return ( state == PASS ); // only allow end with digit
    }
private:
    Input get_input(char i) {
        if (isdigit(i)) return _Digit;
        switch (i) {
            case '.': return _Dot;
            case '-': return _Sign;
            case '+': return _Sign;
            case 'e': return _E;
            case 'E': return _E;
            default: ;// below
        }
        return _Others;
    }
};

int main() {
  Solution solver;
  string test = "+00.e+00";

  cout << solver.isNumber(test) << endl;

  return 0;
}
