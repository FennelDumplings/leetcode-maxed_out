// prob1426: Counting Elements

/*
 * https://leetcode-cn.com/problems/counting-elements/
 */

#include <vector>
#include <unordered_set>

using namespace std;

class Solution {
public:
    int countElements(vector<int>& arr) {
        unordered_set<int> setting(arr.begin(), arr.end());
        int ans = 0;
        for(int x: arr)
            if(setting.count(x + 1) > 0)
                ++ans;
        return ans;
    }
};
