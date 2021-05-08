// prob1552: Magnetic Force Between Two Balls

/*
 * https://leetcode-cn.com/problems/magnetic-force-between-two-balls/
 */

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int maxDistance(vector<int>& position, int m) {
        sort(position.begin(), position.end());
        // n >= 2
        int right = position.back() - position.front(), left = 1;
        while(left < right)
        {
            int mid = left + (right - left + 1) / 2;
            if(check(position, mid, m))
                left = mid;
            else
                right = mid - 1;
        }
        return left;
    }

    bool check(const vector<int>& position, int mid, int m)
    {
        // mid >= 2
        int prev = position[0];
        int cnt = 1;
        // [1..n] 上再放 m - 1 个
        int i = 1;
        int n = position.size();
        while(i < n)
        {
            int pos = position[i];
            if(pos - prev >= mid)
            {
                prev = pos;
                ++cnt;
            }
        }
        return cnt >= m;
    }
};
