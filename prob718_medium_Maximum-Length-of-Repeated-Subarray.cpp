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

using namespace std;

// 类似与字符串哈希的思路, 跑的结果不对, 暂未调通
// p, mod 的质数选取
//     201326611
//     402653189
//     1610612741
// hash[i] = (hash[i-1]*p + idx(A[i - 1])) % MOD; idx(x) = x + 1; i 从 1 开始
//    hash[i] i = 1..n 求出之后，子串 [l..r] 的哈希值可以O(1)获取, 类似与前缀和的思路
//    hash = ((hash[r] - hash[l - 1] * p ^ (r - l + 1)) % mod + mod) % mod
//340ms
class Solution_1_1 {
public:
    int findLength(vector<int>& A, vector<int>& B) {
        int na = A.size(), nb = B.size();
        if(na < nb) return findLength(B, A);
        // na >= nb
        const int MOD = 1610612741;
        const int p = 201326611;
        // 建立 hashA[i] i = 1..na-1
        vector<long long> hashA(na + 1, 0);
        for(int i = 1; i <= na; ++i)
            hashA[i] = (hashA[i - 1] * p + _idx(A[i - 1])) % MOD;
        // 建立 hashB[i] i = 1..nb-1
        vector<long long> hashB(nb + 1, 0);
        vector<long long> p_square(nb + 1, 1);
        for(int i = 1; i <= nb; ++i)
        {
            hashB[i] = (hashB[i - 1] * p + _idx(B[i - 1])) % MOD;
            p_square[i] = (p_square[i - 1] * p) % MOD;
        }
        // 答案在 [1, nb] 之间
        // 对答案二分
        int left = 1, right = nb;
        // 若 mid 长度找到匹配了，说明 result >= mid, left = mid + 1
        // 若 mid 长度没找到匹配，说明 result < mid, right = mid - 1
        // 当 left > right 时结束，答案是 right
        // 先初始化 p 的 k 次方的表 最大到 nb
        while(left <= right)
        {
            int mid = left + (right - left) / 2;
            // A[i] i:0..na-mid -> l i+1:1..na-mid+1 r i+mid:mid..na
            // B[i] 类似
            // hash = ((hash[r] - hash[l - 1] * p ^ (r - l + 1)) % mod + mod) % mod
            bool matched = false;
            for(int i = 0; i <= na - mid; ++i)
            {
                int la = i + 1, ra = i + mid;
                long long hasha = ((hashA[ra] - hashA[la - 1] * p_square[ra - la + 1]) % MOD + MOD) % MOD;
                for(int j = 0; j <= nb - mid; ++j)
                {
                    int lb = j + 1, rb = j + mid;
                    long long hashb = ((hashB[rb] - hashB[lb - 1] * p_square[rb - lb + 1]) % MOD + MOD) % MOD;
                    if(hasha == hashb && _check(A, i, B, j, mid))
                    {
                        matched = true;
                        break;
                    }
                }
                if(matched) break;
            }
            if(matched)
                left = mid + 1;
            else
                right = mid - 1;
        }
        return right;
    }

private:
    bool _check(vector<int>& A, int i, vector<int>& B, int j, int mid)
    {
        for(int k = 0; k < mid; ++k)
        {
            if(A[i + k] != B[j + k])
                return false;
        }
        return true;
    }

    int _idx(int x)
    {
        return x + 1;
    }
};
// 用 unsigned long long 自动取模
class Solution_1_2 {
public:
    int findLength(vector<int>& A, vector<int>& B) {
        int na = A.size(), nb = B.size();
        if(na < nb) return findLength(B, A);
        // na >= nb
        const int p = 201326611;
        // 建立 hashA[i] i = 1..na-1
        vector<unsigned long long> hashA(na + 1, 0);
        for(int i = 1; i <= na; ++i)
            hashA[i] = hashA[i - 1] * p + _idx(A[i - 1]);
        // 建立 hashB[i] i = 1..nb-1
        vector<unsigned long long> hashB(nb + 1, 0);
        vector<unsigned long long> p_square(nb + 1, 1);
        for(int i = 1; i <= nb; ++i)
        {
            hashB[i] = hashB[i - 1] * p + _idx(B[i - 1]);
            p_square[i] = p_square[i - 1] * p;
        }
        // 答案在 [1, nb] 之间
        // 对答案二分
        int left = 1, right = nb;
        // 若 mid 长度找到匹配了，说明 result >= mid, left = mid + 1
        // 若 mid 长度没找到匹配，说明 result < mid, right = mid - 1
        // 当 left > right 时结束，答案是 right
        // 先初始化 p 的 k 次方的表 最大到 nb
        while(left <= right)
        {
            int mid = left + (right - left) / 2;
            // A[i] i:0..na-mid -> l i+1:1..na-mid+1 r i+mid:mid..na
            // B[i] 类似
            // hash = ((hash[r] - hash[l - 1] * p ^ (r - l + 1)) % mod + mod) % mod
            bool matched = false;
            for(int i = 0; i <= na - mid; ++i)
            {
                int la = i + 1, ra = i + mid;
                unsigned long long hasha = hashA[ra] - hashA[la - 1] * p_square[ra - la + 1];
                for(int j = 0; j <= nb - mid; ++j)
                {
                    int lb = j + 1, rb = j + mid;
                    unsigned long long hashb = hashB[rb] - hashB[lb - 1] * p_square[rb - lb + 1];
                    if(hasha == hashb && _check(A, i, B, j, mid))
                    {
                        matched = true;
                        break;
                    }
                }
                if(matched) break;
            }
            if(matched)
                left = mid + 1;
            else
                right = mid - 1;
        }
        return right;
    }

private:
    bool _check(vector<int>& A, int i, vector<int>& B, int j, int mid)
    {
        for(int k = 0; k < mid; ++k)
        {
            if(A[i + k] != B[j + k])
                return false;
        }
        return true;
    }

    int _idx(int x)
    {
        return x + 1;
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
