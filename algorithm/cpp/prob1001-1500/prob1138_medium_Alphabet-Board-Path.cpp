// prob1138: Alphabet Board Path

/*
 * https://leetcode-cn.com/problems/alphabet-board-path/
 */

#include <vector>
#include <string>

using namespace std;

struct Coord
{
    int x, y;
    Coord(int x, int y):x(x),y(y){}
    Coord(){}
};

class Solution {
public:
    string alphabetBoardPath(string target) {
        vector<Coord> coords(26);
        for(int i = 0; i < 26; ++i)
        {
            coords[i].x = i / 5;
            coords[i].y = i % 5;
        }
        string result;
        char iter = 'a';
        for(char ch: target)
        {
            int dx = coords[ch - 'a'].x - coords[iter - 'a'].x;
            int dy = coords[ch - 'a'].y - coords[iter - 'a'].y;
            if(ch == 'z' && (dx != 0 || dy != 0))
            {
                if(dy >= 0)
                    result += string(dy, 'R');
                else
                    result += string(-dy, 'L');
                if(dx >= 0)
                    result += string(dx, 'D');
                else
                    result += string(-dx, 'U');
            }
            else
            {
                if(dx >= 0)
                    result += string(dx, 'D');
                else
                    result += string(-dx, 'U');
                if(dy >= 0)
                    result += string(dy, 'R');
                else
                    result += string(-dy, 'L');
            }
            result += '!';
            iter = ch;
        }
        return result;
    }
};
