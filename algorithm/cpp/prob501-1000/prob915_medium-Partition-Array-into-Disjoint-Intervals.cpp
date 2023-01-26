// prob915: Partition Array into Disjoint Intervals

/*
 * https://leetcode-cn.com/problems/partition-array-into-disjoint-intervals/
 */

#include <vector>

using namespace std;

class Solution {
public:
    int partitionDisjoint(vector<int>& A) {
        int n = A.size();
        vector<int> L(n, A[0]);
        for(int i = 1; i < n; ++i)
            L[i] = max(L[i - 1], A[i]);
        vector<int> R(n, A[n - 1]);
        for(int i = n - 2; i >= 0; --i)
            R[i] = min(R[i + 1], A[i]);
        for(int i = 0; i < n - 1; ++i)
            if(L[i] <= R[i + 1])
                return i + 1;
        return -1;
    }
};
