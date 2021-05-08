// prob718: Maximum Length of Repeated Subarray

/*
 * Given two integer arrays A and B, return the maximum length of an subarray that appears in both arrays.
 */

/*
 * Example 1:
 * Input:
 * A: [1,2,3,2,1]
 * B: [3,2,1,4,7]
 * Output: 3
 * Explanation:
 * The repeated subarray with maximum length is [3, 2, 1].
 */

/*
 * Note:
 * 1 <= len(A), len(B) <= 1000
 * 0 <= A[i], B[i] < 100
 */

#include <vector>
#include <unordered_map>
#include <unordered_set>

using namespace std;

// 用 unsigned long long 自动取模

class Solution {
public:
    int findLength(vector<int>& A, vector<int>& B) {
        int na = A.size(), nb = B.size();
        if(na < nb) return findLength(B, A);
        // na >= nb
        vector<ull> hashA(na + 1, 0);
        for(int i = 1; i <= na; ++i)
            hashA[i] = hashA[i - 1] * p + (ull)A[i - 1];
        vector<ull> hashB(nb + 1, 0);
        vector<ull> pp(nb + 1, 1);
        for(int i = 1; i <= nb; ++i)
        {
            hashB[i] = hashB[i - 1] * p + (ull)B[i - 1];
            pp[i] = pp[i - 1] * p;
        }

        int left = 1, right = nb;
        while(left < right)
        {
            int mid = (left + right + 1) / 2;
            mapping.clear();
            for(int i = 0; i <= na - mid; ++i)
            {
                ull hasha = hashA[i + mid] - hashA[i] * pp[mid];
                mapping[hasha].insert(i);
            }

            bool matched = false;
            for(int j = 0; j <= nb - mid; ++j)
            {
                ull hashb = hashB[j + mid] - hashB[j] * pp[mid];
                if(mapping.count(hashb) > 0)
                    continue;
                for(int i: mapping[hashb])
                    if(check_conflict(A, i, B, j, mid))
                    {
                        matched = true;
                        break;
                    }
            }
            if(matched)
                left = mid;
            else
                right = mid - 1;
        }
        return left;
    }

private:
    using ull = unsigned long long;
    const ull p = 201326611;
    unordered_map<ull, unordered_set<int>> mapping;

    bool check_conflict(vector<int>& A, int i, vector<int>& B, int j, int mid)
    {
        for(int k = 0; k < mid; ++k)
        {
            if(A[i + k] != B[j + k])
                return false;
        }
        return true;
    }
};

// 动态规划
// dp[i][j] := A[i..] B[..] 的最长公共前缀
// max(dp[i][j]) 为答案
// dp[i][j] = dp[i+1][j+1] + 1  (A[i]==B[j])
//          = 0 (A[i]!=B[j])
class Solution {
public:
    int findLength(vector<int>& A, vector<int>& B) {
        int na = A.size(), nb = B.size();
        vector<vector<int> > dp(na + 1, vector<int>(nb + 1, 0));
        int result = 0;
        for(int i = na - 1; i >= 0; --i)
            for(int j = nb - 1; j >= 0; --j)
            {
                if(A[i] == B[j])
                {
                    dp[i][j] = dp[i + 1][j + 1] + 1;
                    result = max(result, dp[i][j]);
                }
            }
        return result;
    }
};
