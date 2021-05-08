// prob1432: Max Difference You Can Get From Changing an Integer

/*
 * https://leetcode-cn.com/problems/max-difference-you-can-get-from-changing-an-integer/
 */

#include <string>
#include <sstream>

using namespace std;

class Solution {
public:
    int maxDiff(int num) {
        // 先找从右到左第一个不是 9 的，将其变为 9
        // 若第一个数字不是 1 则将其变为 1，否则从第二个数字开始，找到第一个不是 0 的
        if(num < 10) return 8;
        string str_min = to_string(num);
        string str_max = str_min;
        int n = str_min.size();
        char target = '9';
        for(int i = 0; i < n; ++i)
        {
            char cur = str_max[i];
            if(cur != '9')
            {
                target = cur;
                break;
            }
        }
        for(char &c: str_max)
            if(c == target)
                c = '9';
        int m1;
        stringstream ss;
        ss << str_max;
        ss >> m1;

        if(str_min[0] != '1')
        {
            target = str_min[0];
            for(char &c: str_min)
                if(c == target)
                    c = '1';
        }
        else
        {
            target = '0';
            for(int i = 1; i < n; ++i)
            {
                char cur = str_min[i];
                if(cur != '0' && cur != '1')
                {
                    target = cur;
                    break;
                }
            }
            for(char &c: str_min)
                if(c == target)
                    c = '0';
        }
        int m2;
        stringstream ss2;
        ss2 << str_min;
        ss2 >> m2;
        return m1 - m2;
    }
};
