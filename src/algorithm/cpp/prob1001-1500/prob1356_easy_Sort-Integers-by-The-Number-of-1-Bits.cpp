// prob1356: Sort Integers by The Number of 1 Bits

/*
 * https://leetcode-cn.com/problems/sort-integers-by-the-number-of-1-bits/
 */

#include <vector>
#include <algorithm>

using namespace std;

struct Cmp
{
    bool operator()(const int& n1, const int& n2) const
    {
        int ones1 = ones(n1);
        int ones2 = ones(n2);
        if(ones1 == ones2)
            return n1 < n2;
        return ones1 < ones2;
    }

    int ones(int x) const
    {
        int cnt = 0;
        while(x)
        {
            x = x & (x - 1);
            ++cnt;
        }
        return cnt;
    }
};

class Solution {
public:
    vector<int> sortByBits(vector<int>& arr) {
        vector<int> result(arr.begin(), arr.end());
        sort(result.begin(), result.end(), Cmp());
        return result;
    }
};
