// prob204: Count Primes

/*
 * Count the number of prime numbers less than a non-negative number, n.
 */

/*
 * Example:
 * Input: 10
 * Output: 4
 * Explanation: There are 4 prime numbers less than 10, they are 2, 3, 5, 7.
 */

#include <vector>

using namespace std;

// 埃氏筛
class Solution {
public:
    int countPrimes(int n) {
        if(n < 2) return 0;
        vector<bool> vec(n, true);
        vec[0] = false;
        vec[1] = false;
        for(int i = 2; i * i < n; ++i)
        {
            if(vec[i])
            {
                for(int j = i * 2; j < n; j += i)
                    vec[j] = false;
            }
        }
        int result = 0;
        for(bool flag: vec)
            if(flag)
                ++result;
        return result;
    }
};

// 优化的埃氏筛
// 内层循环仍然存在计算冗余。
// 比如 n = 25，i = 4 时算法会标记 4 × 2 = 8，4 × 3 = 12 等等数字，但是这两个数字已经被 i = 2 和 i = 3 的 2 × 4 和 3 × 4 标记了。
// 188ms
class Solution_2 {
public:
    int countPrimes(int n) {
        if(n < 2) return 0;
        vector<bool> vec(n, true);
        vec[0] = false;
        vec[1] = false;
        for(int i = 2; i * i < n; ++i)
        {
            if(vec[i])
            {
                for(int j = i * i; j < n; j += i)
                    vec[j] = false;
            }
        }
        int result = 0;
        for(bool flag: vec)
            if(flag)
                ++result;
        return result;
    }
};

// 将 vector<bool> 改成 bool*
// 20ms
class Solution_3 {
public:
    int countPrimes(int n) {
        if(n < 2) return 0;
        bool* vec = new bool[n];
        for(int i = 0; i < n; ++i)
            vec[i] = true;
        vec[0] = false;
        vec[1] = false;
        for(int i = 2; i * i < n; ++i)
        {
            if(vec[i])
            {
                for(int j = i * i; j < n; j += i)
                    vec[j] = false;
            }
        }
        int result = 0;
        for(int i = 0; i < n; ++i)
        {
            bool flag = vec[i];
            if(flag)
                ++result;
        }
        return result;
    }
};

// 线性筛

// Atkin筛

// Wheel筛

// https://euler.stephan-brumme.com/toolbox/#primesieve-eratosthenes
