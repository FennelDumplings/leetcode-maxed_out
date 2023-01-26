// prob1539: Kth Missing Positive Number

/*
 * https://leetcode-cn.com/problems/kth-missing-positive-number/
 */

#include <vector>

using namespace std;

class Solution {
public:
    int findKthPositive(vector<int>& arr, int k) {
        vector<int> tmp;
        int n = arr.size();
        int maxx = 1;
        for(int i = 0; i < n; ++i)
        {
            int cur = arr[i];
            for(int j = maxx; j < cur; ++j)
                tmp.push_back(j);
            maxx = cur + 1;
        }
        int m = tmp.size();
        if(m < k)
            return maxx + k - m - 1;
        return tmp[k - 1];
    }
};
