// prob1646: get Maximum in Generated Array

/*
 * https://leetcode-cn.com/problems/get-maximum-in-generated-array/
 */

#include <vector>

using namespace std;

class Solution {
public:
    int getMaximumGenerated(int n) {
        vector<int> vec(n + 1);
        vec[1] = 1;
        for(int i = 1; i * 2 <= n; ++i)
        {
            vec[i * 2] = vec[i];
            if(i * 2 + 1 <= n)
                vec[i * 2 + 1] = vec[i] + vec[i + 1];
        }
        int ans = vec[0];
        for(int i: vec)
            ans = max(ans, i);
        return ans;
    }
};
