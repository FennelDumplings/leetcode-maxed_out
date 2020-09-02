// prob969: Pancake Sorting

/*
 * https://leetcode-cn.com/problems/pancake-sorting/
 */

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<int> pancakeSort(vector<int>& A) {
        int n = A.size();
        if(n <= 1) return {};
        vector<int> result;
        int iter = n;
        while(iter >= 2)
        {
            int idx = get_idx(A, iter);
            if(idx + 1 < iter)
            {
                result.push_back(idx + 1);
                reverse(A.begin(), A.begin() + idx + 1);
                result.push_back(iter);
                reverse(A.begin(), A.begin() + iter);
            }
            --iter;
        }
        return result;
    }

private:
    int get_idx(const vector<int>& A, int x)
    {
        int n = A.size();
        for(int i = 0; i < n; ++i)
            if(A[i] == x)
                return i;
        return -1;
    }
};
