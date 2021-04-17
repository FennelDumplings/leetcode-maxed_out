// prob1460: Make Two Arrays Equal by Reversing Sub-arrays

/*
 * https://leetcode-cn.com/problems/make-two-arrays-equal-by-reversing-sub-arrays/
 */


#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    bool canBeEqual(vector<int>& target, vector<int>& arr) {
        int n = target.size(), m = arr.size();
        if(n != m) return false;
        sort(target.begin(), target.end());
        sort(arr.begin(), arr.end());
        for(int i = 0; i < n; ++i)
            if(arr[i] != target[i])
                return false;
        return true;
    }
};
