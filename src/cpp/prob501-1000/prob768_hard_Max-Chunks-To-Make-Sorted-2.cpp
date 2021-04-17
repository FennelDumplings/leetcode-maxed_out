// prob768: Max Chunks To Make Sorted II

/*
 * https://leetcode-cn.com/problems/max-chunks-to-make-sorted-ii/j
 */

#include <vector>
#include <algorithm>
#include <unordered_set>

using namespace std;

// unordered_multiset
class Solution_2 {
public:
    int maxChunksToSorted(vector<int>& arr) {
        int n = arr.size();
        int i = 0;
        unordered_multiset<int> setting;
        vector<int> sorted = arr;
        sort(sorted.begin(), sorted.end());
        int iter = 0;
        int ans = 0;
        while(i < n)
        {
            int idx = lower_bound(sorted.begin(), sorted.end(), arr[i]) - sorted.begin();
            if(idx <= i) // 此时应该有 i == iter
            {
                ++iter;
                ++ans;
                ++i;
                continue;
            }
            for(int k = iter; k < idx; ++k)
                setting.insert(sorted[k]);
            int maxx = arr[i];
            iter = idx + 1;
            int j = i + 1;
            while(j < n && !setting.empty())
            {
                if(arr[j] < maxx)
                    setting.erase(setting.find(arr[j]));
                else if(arr[j] == maxx)
                    ++iter;
                else
                {
                    int idx = lower_bound(sorted.begin(), sorted.end(), arr[j]) - sorted.begin();
                    for(int k = iter; k < idx; ++k)
                        setting.insert(sorted[k]);
                    iter = idx + 1;
                    maxx = arr[j];
                }
                ++j;
            }
            // 此时应该有 j == iter
            ++i;
            ++ans;
            i = iter;
        }
        return ans;
    }
};

// 单调栈
// 对 i，找到 [i+1..n-1] 上 < arr[i] 的最远的 j, 当前块至少是 [i..j]

#include <stack>

class Solution {
public:
    int maxChunksToSorted(vector<int>& arr) {
        stack<int> st;
        for(int a: arr)
        {
            int maxx = a;
            while(!st.empty() && st.top() > a)
            {
                maxx = max(st.top(), maxx);
                st.pop();
            }
            st.push(maxx);
        }
        return st.size();
    }
};
