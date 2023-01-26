// interview17.21: 直方图的水量

/*
 * https://leetcode-cn.com/problems/volume-of-histogram-lcci/
 */

#include <vector>
#include <deque>

using namespace std;

class Solution {
public:
    int trap(vector<int>& height) {
        if(height.empty()) return 0;
        int n = height.size();
        if(n <= 2) return 0;
        deque<int> deq;
        int ans = 0;
        for(int i = 0; i < n; ++i)
        {
            while(!deq.empty() && height[deq.back()] <= height[i])
            {
                int h = height[deq.back()];
                deq.pop_back();
                if(!deq.empty())
                {
                    int dh = min(height[deq.back()], height[i]) - h;
                    int w = i - deq.back() - 1;
                    ans += dh * w;
                }
            }
            deq.push_back(i);
        }
        return ans;
    }
};
