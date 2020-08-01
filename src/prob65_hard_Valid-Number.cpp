// prob65: Valid Number

/*
 *
 * Validate if a given string can be interpreted as a decimal number.
 * Some examples:
 * "0" => true
 * " 0.1 " => true
 * "abc" => false
 * "1 a" => false
 * "2e10" => true
 * " -90e3   " => true
 * " 1e" => false
 * "e3" => false
 * " 6e-1" => true
 * " 99e2.5 " => false
 * "53.5e93" => true
 * " --6 " => false
 * "-+3" => false
 * "95a54e53" => false
 */

/*
 * Note: It is intended for the problem statement to be ambiguous.
 * You should gather all requirements up front before implementing one.
 * However, here is a list of characters that can be in a valid decimal number:
 * Numbers 0-9
 * Exponent - "e"
 * Positive/negative sign - "+"/"-"
 * Decimal point - "."
 */

#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    bool isNumber(string s) {
        if(s.empty()) return false;
        int n = s.size();

        int state = 0;
        vector<bool> finals({0, 0, 0, 1, 0, 1, 1, 0, 1}); // 合法的终止状态
        vector<vector<int> > transfer({
                {0,  1,  6,  2,  -1, -1},
                {-1, -1, 6,  2,  -1, -1},
                {-1, -1, 3,  -1, -1, -1},
                {8,  -1, 3,  -1, 4,  -1},
                {-1, 7,  5,  -1, -1, -1},
                {8,  -1, 5,  -1, -1, -1},
                {8,  -1, 6,  3,  4,  -1},
                {-1, -1, 5,  -1, -1, -1},
                {8,  -1, -1, -1, -1, -1},
                });

        for(int i = 0; i < n; ++i)
        {
            state = transfer[state][_make(s[i])];
            if(state < 0) return false;
        }
        return finals[state];
    }

private:
    int _make(const char& c)
    {
        switch(c)
        {
            case ' ': return 0;
            case '+': return 1;
            case '-': return 1;
            case '.': return 3;
            case 'e': return 4;
            default: return _number(c);
        }
    }

    int _number(char c)
    {
        if(c >= '0' && c <= '9')
            return 2;
        else
            return 5;
    }
};

#include <regex>

class Solution_2 {
public:
    bool isNumber(string s) {
        regex reg("^\\s*[+-]?(\\.\\d+|\\d+\\.?\\d*)([eE][+-]?\\d+)?\\s*$");
        bool flag = regex_match(s, reg);
        return flag;
    }
};
