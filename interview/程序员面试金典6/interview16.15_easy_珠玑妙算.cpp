// interview16.15: 珠玑妙算

/*
 * https://leetcode-cn.com/problems/master-mind-lcci/
 */

#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    vector<int> masterMind(string solution, string guess) {
        vector<int> cnts(4);
        int n = solution.size();
        for(int i = 0; i < n; ++i)
        {
            ++cnts[idx(solution[i])];
        }
        vector<int> result(2, 0);
        for(int i = 0; i < n; ++i)
        {
            if(solution[i] == guess[i])
            {
                ++result[0];
                --cnts[idx(guess[i])];
            }
        }
        for(int i = 0; i < n; ++i)
        {
            if(solution[i] != guess[i])
            {
                if(cnts[idx(guess[i])] > 0)
                {
                    ++result[1];
                    --cnts[idx(guess[i])];
                }
            }
        }
        return result;
    }

private:
    int idx(char ch)
    {
        switch(ch)
        {
            case('R'): return 0;
            case('Y'): return 1;
            case('G'): return 2;
            case('B'): return 3;
            default: return -1;
        }
    }
};
