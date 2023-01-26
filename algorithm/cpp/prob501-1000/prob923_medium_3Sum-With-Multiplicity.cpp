// prob923: 3Sum With Multiplicity

/*
 * Given an integer array A, and an integer target, return the number of tuples i, j, k
 * such that i < j < k and A[i] + A[j] + A[k] == target.
 * As the answer can be very large, return it modulo 10^9 + 7.
 */

/*
 * Example 1:
 * Input: A = [1,1,2,2,3,3,4,4,5,5], target = 8
 * Output: 20
 * Explanation:
 * Enumerating by the values (A[i], A[j], A[k]):
 * (1, 2, 5) occurs 8 times;
 * (1, 3, 4) occurs 8 times;
 * (2, 2, 4) occurs 2 times;
 * (2, 3, 3) occurs 2 times.
 * Example 2:
 * Input: A = [1,1,2,2,2,2], target = 5
 * Output: 12
 * Explanation:
 * A[i] = 1, A[j] = A[k] = 2 occurs 12 times:
 * We choose one 1 from [1,1] in 2 ways,
 * and two 2s from [2,2,2,2] in 6 ways.
 */

#include <vector>
#include <algorithm>

using namespace std;

// A[i] = [0..100] 计数排序
// A.size = [0..3000] -> 1000 * 1000 * 1000 = 10 ^ 9 < int范围
// target = [0..300]
class Solution {
public:
    int threeSumMulti(vector<int>& A, int target) {
        if(A.empty()) return 0;
        int n = A.size();
        if(n < 3) return 0;

        int MOD = 1000000007;
        int N = 101;
        vector<int> cnt(N, 0);
        for(int num: A)
            ++cnt[num];
        for(int i = 0, k = 0; i < N; ++i)
        {
            int count = cnt[i];
            while(count > 0)
            {
                A[k++] = i;
                --count;
            }
        }

        ll result = 0;
        int i = 0;
        while(i <= n - 3)
        {
            int gap = target - A[i];
            int left = i + 1, right = n - 1;
            while(left < right)
            {
                if(A[left] + A[right] == gap)
                {
                    result = (result + _counting(cnt, A[i], A[left], A[right])) % MOD;
                    right = right - cnt[A[right]];
                    if(A[i] == A[left])
                        left = left + (cnt[A[left]] - 1);
                    else
                        left = left + cnt[A[left]];
                }
                else if(A[left] + A[right] > gap) // right 左移
                {
                    right = right - cnt[A[right]];
                }
                else // left 右移
                {
                    if(A[i] == A[left])
                        left = left + (cnt[A[left]] - 1);
                    else
                        left = left + cnt[A[left]];
                }
            }
            i = i + cnt[A[i]];
        }
        return (int)result;
    }

private:
    using ll = long long;

    ll _counting(const vector<int>& cnt, int ai, int al, int ar)
    {
        // ai <= al <= ar
        // 可以按照下面的四种情况通过分别遍历 cnt 数组来计数
        if(ai == al && al == ar)
            return ((ll)cnt[ai] * (cnt[ai] - 1) * (cnt[ai] - 2)) / 6;
        else if(ai == al && al < ar)
            return ((ll)cnt[ai] * (cnt[ai] - 1)) * cnt[ar] / 2;
        else if(ai < al && al == ar)
            return (ll)cnt[ai] * (cnt[ar] * (cnt[ar] - 1)) / 2;
        else
            return (ll)cnt[ai] * cnt[al] * cnt[ar];
    }
};


// 计数排序后不遍历 A, 直接对 cnt 里的结果按照三数相同，前两数相同，后两数相同，三数不同
// 四中情况分别枚举
// 可以按照下面的四种情况通过分别遍历 cnt 数组来计数
class Solution_2 {
public:
    int threeSumMulti(vector<int>& A, int target) {
        if(A.empty()) return 0;
        int n = A.size();
        if(n < 3) return 0;

        int MOD = 1000000007;
        int N = 101;
        vector<int> cnt(N, 0);
        for(int num: A)
            ++cnt[num];
        for(int i = 0, k = 0; i < N; ++i)
        {
            int count = cnt[i];
            while(count > 0)
            {
                A[k++] = i;
                --count;
            }
        }

        ll result = 0;
        // 三数相同
        for(int i = 0; i < N; ++i)
        {
            if(cnt[i] >= 3 && i * 3 == target)
            {
                result = (result + ((ll)cnt[i] * (cnt[i] - 1) * (cnt[i] - 2)) / 6) % MOD;
                break;
            }
        }
        // 前两数相同
        for(int i = 0; i < N - 1; ++i)
        {
            if(cnt[i] >= 2)
            {
                for(int j = i + 1; j < N; ++j)
                {
                    if(i * 2 + j == target)
                    {
                        result = (result + ((ll)cnt[i] * (cnt[i] - 1)) * cnt[j] / 2) % MOD;
                        break;
                    }
                }
            }
        }
        // 后两数相同
        for(int i = 0; i < N - 1; ++i)
        {
            for(int j = i + 1; j < N; ++j)
            {
                if(cnt[j] >= 2 && i + j * 2 == target)
                {
                    result = (result + (ll)cnt[i] * ((cnt[j] - 1) * cnt[j]) / 2) % MOD;
                    break;
                }
            }
        }
        // 三数不同
        for(int i = 0; i < N - 2; ++i)
            for(int j = i + 1; j < N - 1; ++j)
                for(int k = j + 1; k < N; ++k)
                {
                    if(i + j + k == target)
                    {
                        result = (result + (ll)cnt[i] * cnt[j] * cnt[k]) % MOD;
                        break;
                    }
                }

        return (int)result;
    }

private:
    using ll = long long;
};
