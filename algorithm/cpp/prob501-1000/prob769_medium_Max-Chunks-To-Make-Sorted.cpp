// prob769: Max Chunks To Make Sorted

/*
 * https://leetcode-cn.com/problems/max-chunks-to-make-sorted/
 */

#include <vector>
#include <unordered_set>

using namespace std;

class Solution {
public:
    int maxChunksToSorted(vector<int>& arr) {
        int n = arr.size();
        int ans = 0;
        int i = 0;
        unordered_set<int> setting;
        while(i < n)
        {
            if(arr[i] == i)
            {
                ++ans;
                ++i;
                continue;
            }
            int maxx = arr[i];
            for(int k = i; k < maxx; ++k)
                setting.insert(k);
            int j = i + 1;
            while(j < n && !setting.empty())
            {
                if(arr[j] < maxx)
                    setting.erase(arr[j]);
                else
                {
                    for(int k = maxx + 1; k < arr[j]; ++k)
                        setting.insert(k);
                    maxx = arr[j];
                }
                ++j;
            }
            ++ans;
            i = j;
        }
        return ans;
    }
};
