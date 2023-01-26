// prob1404: Number of Steps to Reduce a Number in Binary Representation to One

/*
 * https://leetcode-cn.com/problems/number-of-steps-to-reduce-a-number-in-binary-representation-to-one/
 */

#include <string>
#include <list>
#include <vector>

using namespace std;

class Solution {
public:
    int numSteps(string s) {
        int ans = 0;
        list<char> l(s.begin(), s.end());
        while(!(l.size() == 1 && l.back() == '1'))
        {
            if(l.back() == '1')
                add(l);
            else
                divide(l);
            ++ans;
        }
        return ans;
    }

private:
    void add(list<char>& l)
    {
        auto it = l.rbegin();
        while(it != l.rend() && *it == '1')
        {
            *it = '0';
            ++it;
        }
        if(it == l.rend())
            l.push_front('1');
        else
            *it = '1';
    }

    void divide(list<char>& l)
    {
        l.pop_back();
    }
};
