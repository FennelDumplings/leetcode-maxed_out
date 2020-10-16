
#include <string>

using namespace std;

class Solution {
public:
    int calculate(string s) {
        int x = 1, y = 0;
        for(int c: s)
        {
            if(c == 'A')
                funcA(x, y);
            else
                funcB(x, y);
        }
        return x + y;
    }

private:
    // "A" 运算：使 x = 2 * x + y；
    // "B" 运算：使 y = 2 * y + x。

    void funcA(int& x, int& y)
    {
        x = 2 * x + y;
    }

    void funcB(int& x, int & y)
    {
        y = y * 2 + x;
    }
};
