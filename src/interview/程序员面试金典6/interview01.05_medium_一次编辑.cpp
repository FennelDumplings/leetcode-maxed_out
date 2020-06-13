// interview01.05: 一次编辑

/*
 * 字符串有三种编辑操作:插入一个字符、删除一个字符或者替换一个字符。 给定两个字符串，编写一个函数判定它们是否只需要一次(或者零次)编辑。
 */

/*
 * 示例 1:
 * 输入:
 * first = "pale"
 * second = "ple"
 * 输出: True
 * 示例 2:
 * 输入:
 * first = "pales"
 * second = "pal"
 * 输出: False
 */

#include <string>
#include <cmath>

using namespace std;

class Solution {
public:
    bool oneEditAway(string first, string second) {
        int n1 = first.size(), n2 = second.size();
        if(abs(n1 - n2) > 1)
            return false;
        if(n1 == n2)
        {
            bool flag = false;
            for(int i = 0; i < n1; ++i)
            {
                if(first[i] != second[i])
                {
                    if(flag)
                        return false;
                    flag = true;
                }
            }
        }
        else if(n1 > n2)
        {
            bool flag = false;
            int i = 0, j = 0;
            while(i < n1 && j < n2)
            {
                if(first[i] != second[j])
                {
                    if(flag)
                        return false;
                    flag = true;
                    ++i;
                }
                else
                {
                    ++i;
                    ++j;
                }
            }
        }
        else
        {
            return oneEditAway(second, first);
        }
        return true;
    }
};
