// 20200531
// 2. 切割后面积最大的蛋糕


#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int maxArea(int h, int w, vector<int>& horizontalCuts, vector<int>& verticalCuts) {
        int MOD = 1e9 + 7;
        int nh = horizontalCuts.size(), nv = verticalCuts.size();
        sort(horizontalCuts.begin(), horizontalCuts.end());
        sort(verticalCuts.begin(), verticalCuts.end());
        vector<int> diff_h(nh + 1);
        vector<int> diff_v(nv + 1);
        for(int i = 0; i < nh; ++i)
        {
            if(i == 0)
            {
                diff_h.push_back(horizontalCuts[i] - 0);
                continue;
            }
            diff_h.push_back(horizontalCuts[i] - horizontalCuts[i - 1]);
        }
        diff_h.push_back(h - horizontalCuts.back());
        for(int i = 0; i < nv; ++i)
        {
            if(i == 0)
            {
                diff_v.push_back(verticalCuts[i] - 0);
                continue;
            }
            diff_v.push_back(verticalCuts[i] - verticalCuts[i - 1]);
        }
        diff_v.push_back(w - verticalCuts.back());
        auto it_h = max_element(diff_h.begin(), diff_h.end());
        auto it_v = max_element(diff_v.begin(), diff_v.end());
        return ((long long)(*it_h) * (*it_v)) % MOD;
    }
};
