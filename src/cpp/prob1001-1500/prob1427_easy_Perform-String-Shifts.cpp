// prob1427: Perform String Shifts

/*
 * https://leetcode-cn.com/problems/perform-string-shifts/
 */

#include <string>
#include <list>
#include <vector>

using namespace std;

class Solution {
public:
    string stringShift(string s, vector<vector<int>>& shift) {
        list<char> l(s.begin(), s.end());
        for(vector<int> &op: shift)
        {
            int d = op[0];
            int k = op[1];
            if(d == 0)
            {
                for(int i = 0; i < k; ++i)
                {
                    char ch = l.front();
                    l.pop_front();
                    l.push_back(ch);
                }
            }
            else
            {
                for(int i = 0; i < k; ++i)
                {
                    char ch = l.back();
                    l.pop_back();
                    l.push_front(ch);
                }
            }
        }
        return string(l.begin(), l.end());
    }
};
