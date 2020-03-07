// prob372: Super Pow

/*
 * Given a set of non-overlapping intervals, insert a new interval into the intervals (merge if necessary).
 * You may assume that the intervals were initially sorted according to their start times.
 */

/*
 * Example 1:
 * Input: intervals = [[1,3],[6,9]], newInterval = [2,5]
 * Output: [[1,5],[6,9]]
 * Example 2:
 * Input: intervals = [[1,2],[3,5],[6,7],[8,10],[12,16]], newInterval = [4,8]
 * Output: [[1,2],[3,10],[12,16]]
 * Explanation: Because the new interval [4,8] overlaps with [3,5],[6,7],[8,10].
 */

/*
 * NOTE: input types have been changed on April 15, 2019. Please reset to default code definition to get new method signature.
 */

#include <vector>

using namespace std;

class Solution {
public:
    int superPow(int a, vector<int>& b) {
        // a > 0, b > 0
        int len = b.size();
        int ans = 1;
        a %= M;
        for(int i = len - 1; i >= 0; --i)
        {
            if(b[i] != 0)
                ans = (ans * _power(a, b[i])) % M;
            a = _power10(a);
        }
        return ans;
    }

private:
    const int M = 1337;

    int _power10(int a)
    {
        int n = 10;
        int ans = 1;
        while(n)
        {
            if(n & 1)
                ans = (ans * a) % M;
            a = (a * a) % M;
            n >>= 1;
        }
        return ans;
    }

    int _power(int a, int n)
    {
        int ans = 1;
        while(n)
        {
            if(n & 1)
                ans = (ans * a) % M;
            a = (a * a) % M;
            n >>= 1;
        }
        return ans;
    }
};
