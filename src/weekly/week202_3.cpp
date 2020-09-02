

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int maxDistance(vector<int>& position, int m) {
        sort(position.begin(), position.end());
        // n >= 2
        int right = 1e9 - 1, left = 1;
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

private:
    bool check(const vector<int>& position, int mid, int m)
    {
        // mid >= 2
        int pos = position[0];
        // [1..n] 上再放 m - 1 个
        --m;
        int i = 1;
        int n = position.size();
        while(i < n)
        {
            int target = pos + mid;
            // 找 position 中 >= target 的最小位置
            auto it = lower_bound(position.begin(), position.end(), target);
            if(it == position.end())
                return false;
            i = it - position.begin();
            pos = position[i];
            --m;
            if(m == 0)
                return true;
        }
        return false;
    }
};
