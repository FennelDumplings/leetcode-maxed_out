// prob1238: Circular Permutation in Binary Representation

/*
 * https://leetcode-cn.com/problems/circular-permutation-in-binary-representation/
 */

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<int> circularPermutation(int n, int start) {
        // 0 -> 1
        vector<int> result(1 << n);
        int idx = -1;
        for(int i = 0; i < (1 << n); ++i)
        {
            result[i] = i ^ (i >> 1);
            if(result[i] == start)
                idx = i;
        }
        rotate(result.begin(), result.begin() + idx, result.end());
        return result;
    }
};
