// prob1399: Count Largest Group

/*
 * https://leetcode-cn.com/problems/count-largest-group/
 */

#include <unordered_map>

using namespace std;

class Solution {
public:
    int countLargestGroup(int n) {
        unordered_map<int, int> mapping;
        for(int i = 1; i <= n; ++i)
        {
            ++mapping[_sum(i)];
        }
        int ans = 0;
        int max_cnt = 0;
        for(auto item: mapping)
        {
            if(item.second > max_cnt)
            {
                max_cnt = item.second;
                ans = 1;
            }
            else if(item.second == max_cnt)
            {
                ++ans;
            }
        }
        return ans;
    }

private:
    int _sum(int i)
    {
        int ans = 0;
        while(i)
        {
            ans += (i % 10);
            i /= 10;
        }
        return ans;
    }
};
