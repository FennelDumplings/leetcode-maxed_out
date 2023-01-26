// prob1299: Replace Elements with Greatest Element on Right Side

/*
 * https://leetcode-cn.com/problems/replace-elements-with-greatest-element-on-right-side/
 */

#include <vector>

using namespace std;

class Solution {
public:
    vector<int> replaceElements(vector<int>& arr) {
        int n = arr.size();
        vector<int> result(n);
        int maxx = -1;
        for(int i = n - 1; i >= 0; --i)
        {
            result[i] = maxx;
            maxx = max(maxx, arr[i]);
        }
        return result;
    }
};
