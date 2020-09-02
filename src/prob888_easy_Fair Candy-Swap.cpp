// prob888: Fair Candy Swap

/*
 * https://leetcode-cn.com/problems/fair-candy-swap/
 */

#include <vector>
#include <numeric>
#include <cmath>

using namespace std;

class Solution {
public:
    vector<int> fairCandySwap(vector<int>& A, vector<int>& B) {
        int sum1 = accumulate(A.begin(), A.end(), 0);
        int sum2 = accumulate(B.begin(), B.end(), 0);
        int diff =  abs(sum1 - sum2);
        vector<int> result;
        if(sum1 > sum2)
            result = _find(A, B, diff);
        else
        {
            result = _find(B, A, diff);
            swap(result[0], result[1]);
        }
        return result;
    }

private:
    vector<int> _find(const vector<int>& A, const vector<int>& B, int diff)
    {
        // sum(A) > sum(B)
        // sum(A) - Sum(B) = diff
        if(diff & 1) return {-1, -1};
        vector<bool> flagA(1e5 + 1, false);
        for(int a: A)
            flagA[a] = true;
        for(int b: B)
        {
            int t = b + diff / 2;
            if(t <= 1e5 && flagA[t])
                return {t, b};
        }
        return {-1, -1};
    }
};
