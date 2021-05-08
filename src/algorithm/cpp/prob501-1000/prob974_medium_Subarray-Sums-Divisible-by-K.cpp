// prob974: Subarray Sums Divisible by K

/*
 * Given an array A of integers, return the number of (contiguous, non-empty) subarrays that have a sum divisible by K.
 */

/*
 * Example 1:
 * Input: A = [4,5,0,-2,-3,1], K = 5
 * Output: 7
 */

/*
 * Note:
 * 1 <= A.length <= 30000
 * -10000 <= A[i] <= 10000
 *  2 <= K <= 10000
 */

#include <vector>
#include <unordered_set>
#include <unordered_map>

using namespace std;

// 前缀和解法，O(N^2)
// TLE
class Solution {
public:
    int subarraysDivByK(vector<int>& A, int K) {
        if(A.empty()) return 0;
        int n = A.size();
        vector<int> sums(n + 1, 0);
        for(int i = 1; i <= n; ++i)
            sums[i] = sums[i - 1] + A[i - 1];
        int result = 0;
        for(int i = 0; i < n; ++i)
        {
            for(int j = i + 1; j <= n; ++j)
                if(check(sums[j] - sums[i], K))
                    ++result;
        }
        return result;
    }

private:
    bool check(int sum, int K)
    {
        if(K == 0) return false;
        else if(sum == 0) return true;
        return sum % K == 0;
    }
};

// 用 unordered_multiset 也会超时
class Solution_optim {
public:
    int subarraysDivByK(vector<int>& A, int K) {
        if(A.empty()) return 0;
        int n = A.size();
        unordered_multiset<int> setting;
        setting.insert(0);
        vector<int> sums(n + 1, 0);
        int result = 0;
        for(int i = 1; i < n + 1; ++i)
        {
            sums[i] = sums[i - 1] + A[i - 1];
            if(sums[i] < 0)
            {
                result += setting.count(sums[i] % K + K);
                setting.insert(sums[i] % K + K);
            }
            else
            {
                result += setting.count(sums[i] % K);
                setting.insert(sums[i] % K);
            }
        }
        return result;
    }
};

// 用 unordered_map 不超时
// 负数的余数是向0取整的
class Solution_optim2 {
public:
    int subarraysDivByK(vector<int>& A, int K) {
        if(A.empty()) return 0;
        int n = A.size();
        unordered_map<int, int> sum_count;
        sum_count.insert(pair<int, int>(0, 1)); // 0 要初始化进去
        vector<int> sums(n + 1, 0);
        int result = 0;
        for(int i = 1; i < n + 1; ++i)
        {
            sums[i] = sums[i - 1] + A[i - 1];
            if(sums[i] < 0)
            {
                if(sum_count.find((sums[i] % K + K) % K) != sum_count.end())
                {
                    result += sum_count[(sums[i] % K + K) % K];
                    sum_count[(sums[i] % K + K) % K]++;
                }
                else
                    sum_count.insert(pair<int, int>((sums[i] % K + K) % K, 1));
            }
            else
            {
                if(sum_count.find(sums[i] % K) != sum_count.end())
                {
                    result += sum_count[sums[i] % K];
                    sum_count[sums[i] % K]++;
                }
                else
                    sum_count.insert(pair<int, int>(sums[i] % K, 1));
            }
        }
        return result;
    }
};

// nums[i] < 0 时候，做同余处理
class Solution_optim3 {
public:
    int subarraysDivByK(vector<int>& A, int K) {
        if(A.empty()) return 0;
        int n = A.size();
        unordered_map<int, int> sum_count;
        sum_count.insert(pair<int, int>(0, 1)); // 0 要初始化进去
        vector<int> sums(n + 1, 0);
        int result = 0;
        for(int i = 1; i < n + 1; ++i)
        {
            sums[i] = sums[i - 1] + A[i - 1];
            if(sums[i] < 0) // 同余处理
                sums[i] = K - abs(sums[i]) % K;
            if(sum_count.find(sums[i] % K) != sum_count.end())
            {
                result += sum_count[sums[i] % K];
                sum_count[sums[i] % K]++;
            }
            else
                sum_count.insert(pair<int, int>(sums[i] % K, 1));
        }
        return result;
    }
};

// K 范围不大，用 vector<int> 做哈希表
// sums 的空间可优化
class Solution_optim4 {
public:
    int subarraysDivByK(vector<int>& A, int K) {
        if(A.empty()) return 0;
        int n = A.size();
        vector<int> sum_count(K, 0);
        sum_count[0] = 1; // 0 要初始化进去
        int result = 0;
        int sum = 0;
        for(int i = 1; i < n + 1; ++i)
        {
            sum = sum + A[i - 1];
            if(sum < 0) // 同余处理
                sum = K - abs(sum) % K;
            result += sum_count[sum % K];
            sum_count[sum % K]++;
        }
        return result;
    }
};
