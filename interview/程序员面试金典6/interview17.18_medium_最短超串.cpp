// interview17.18: 最短超串

/*
 * https://leetcode-cn.com/problems/shortest-supersequence-lcci/
 */

#include <set>
#include <unordered_set>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
public:
    vector<int> shortestSeq(vector<int>& big, vector<int>& small) {
        int n = big.size(), m = small.size();
        if(n < m) return {};
        unordered_set<int> setting(small.begin(), small.end());
        unordered_map<int, set<int>> window_nums;
        int min_len = n + 1;
        int result_left = -1;
        int left = 0;
        while(left < n && setting.count(big[left]) == 0)
            ++left;
        int right = left;
        while(left < n && right < n)
        {
            while(right < n && (int)window_nums.size() < m)
            {
                if(setting.count(big[right]) > 0)
                {
                    window_nums[big[right]].insert(right);
                }
                ++right;
            }
            if((int)window_nums.size() < m) break;
            while((int)window_nums.size() == m)
            {
                if(setting.count(big[left]) > 0)
                {
                    window_nums[big[left]].erase(window_nums[big[left]].find(left));
                    if(window_nums[big[left]].empty())
                        window_nums.erase(window_nums.find(big[left]));
                }
                ++left;
            }
            int len = right - left + 1;
            if(len < min_len)
            {
                min_len = len;
                result_left = left - 1;
            }
            while(left < n && setting.count(big[left]) == 0)
                ++left;
        }
        if(result_left == -1) return {};
        return vector<int>{result_left, result_left + min_len - 1};
    }
};
