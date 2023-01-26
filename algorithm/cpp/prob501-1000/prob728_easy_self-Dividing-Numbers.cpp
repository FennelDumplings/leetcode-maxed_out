// prob728: self Dividing Numbers

/*
 * https://leetcode-cn.com/problems/self-dividing-numbers/
 */

#include <vector>

using namespace std;

class Solution {
public:
    vector<int> selfDividingNumbers(int left, int right) {
        vector<int> result;
        for(int i = left; i <= right; ++i)
            if(check(i))
                result.push_back(i);
        return result;
    }

private:
    bool check(int x)
    {
        int i = x;
        while(i)
        {
            if(i % 10 == 0)
                return false;
            if(x % (i % 10) != 0)
                return false;
            i /= 10;
        }
        return true;
    }
};
