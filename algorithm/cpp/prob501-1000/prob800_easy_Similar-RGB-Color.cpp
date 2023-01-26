// prob800: Similar RGB Color

/*
 * https://leetcode-cn.com/problems/similar-rgb-color/
 */

#include <string>
#include <climits>
#include <unordered_map>

using namespace std;

class Solution {
public:
    string similarRGB(string color) {
        string result = "#";
        result += _find(color.substr(1, 2));
        result += _find(color.substr(3, 2));
        result += _find(color.substr(5, 2));
        return result;
    }

private:
    int mapping(char ch)
    {
        if(ch >= '0' && ch <= '9')
            return ch - '0';
        return 10 + ch - 'a';
    }

    string _find(const string& a)
    {
        // a = xy
        int min_diff =  INT_MAX;
        string result = "##";
        for(char ch: string("0123456789abcdef"))
        {
            int diff = dist(a, string(2, ch));
            if(diff < min_diff)
            {
                min_diff = diff;
                result = string(2, ch);
            }
        }
        return result;
    }

    int dist(string a1, string a2)
    {
        int diff = mapping(a1[0]) - mapping(a2[0]);
        diff *= 16;
        diff += mapping(a1[1]) - mapping(a2[1]);
        return abs(diff);
    }
};
