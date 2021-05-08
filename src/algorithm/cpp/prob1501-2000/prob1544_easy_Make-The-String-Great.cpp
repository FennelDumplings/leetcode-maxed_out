// prob1544: Make The String Great

/*
 * https://leetcode-cn.com/problems/make-the-string-great/
 */


#include <string>
#include <list>
#include <cmath>

using namespace std;

class Solution {
public:
    string makeGood(string s) {
        list<char> l(s.begin(), s.end());
        bool flag = true;
        while(flag)
            flag = check(l);
        string result(l.begin(), l.end());
        return result;
    }

private:
    const int DIFF = 'a' - 'A';

    bool check(list<char>& l)
    {
        bool flag = false;
        auto it = l.begin();
        while(it != (--l.end()))
        {
            if(abs(*it - *(++it)) == DIFF)
            {
                flag = true;
                --it;
                it = l.erase(it);
                it = l.erase(it);
            }
        }
        return flag;
    }
};
