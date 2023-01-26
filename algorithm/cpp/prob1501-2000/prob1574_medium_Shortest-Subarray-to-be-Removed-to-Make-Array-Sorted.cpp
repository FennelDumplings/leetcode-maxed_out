// prob1574: Shortest Subarray to be Removed to Make Array Sorted

/*
 * https://leetcode-cn.com/problems/shortest-subarray-to-be-removed-to-make-array-sorted/
 */

#include <vector>

using namespace std;

class Solution {
public:
    int findLengthOfShortestSubarray(vector<int>& arr) {
        int n = arr.size();
        if(n == 1) return 0;
        // 找第一个峰点；
        int L = n;
        for(int i = 0; i < n - 1; ++i)
            if(arr[i] > arr[i + 1])
            {
                L = i;
                break;
            }
        // 找第一个谷点
        int R = -1;
        for(int i = n - 1; i >= 1; --i)
            if(arr[i] < arr[i - 1])
            {
                R = i;
                break;
            }
        if(R <= L)
            return 0;

        // [L, R] 至少 R - L 需要删掉，两侧可能还要多
        int l = L;
        for(int i = 0; i <= L; ++i)
            if(arr[i] > arr[R])
            {
                l = i;
                break;
            }
        int r = R;
        for(int i = n - 1; i >= R; --i)
            if(arr[i] < arr[L])
            {
                r = i;
                break;
            }
        int ans = l + (n - 1 - R) + 1; // [l..L] 一个都不取
        for(int i = l, k = R; i <= L; ++i) // [l..L] 取到 [l..i]
        {
            while(k <= r && arr[k] < arr[i])
                ++k;
            ans = max(ans, i + 1 + (n - k));
        }
        // ans = max(ans, max(L + 1, n - R));
        return n - ans;
    }
};
