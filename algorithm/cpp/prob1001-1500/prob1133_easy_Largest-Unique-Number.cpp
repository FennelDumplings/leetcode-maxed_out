// prob1133: Largest Unique Number

/*
 * https://leetcode-cn.com/problems/largest-unique-number/
 */

#include <vector>
#include <unordered_set>

using namespace std;

class Solution {
public:
    int largestUniqueNumber(vector<int>& A) {
        int n = A.size();
        unordered_set<int> cand;
        unordered_set<int> labeled;
        for(int i = 0; i < n; ++i)
        {
            if(labeled.count(A[i]))
                continue;
            if(cand.count(A[i]) == 0)
                cand.insert(A[i]);
            else
            {
                cand.erase(A[i]);
                labeled.insert(A[i]);
            }
        }
        if(cand.empty())
            return -1;
        int ans = *cand.begin();
        for(int i: cand)
            ans = max(ans, i);
        return ans;
    }
};
