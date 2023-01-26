// prob1390: Four Divisors

/*
 * Given an integer array nums, return the sum of divisors of the integers in that array that have exactly four divisors.
 * If there is no such integer in the array, return 0.
 */

/*
 * Example 1:
 * Input: nums = [21,4,7]
 * Output: 32
 * Explanation:
 * 21 has 4 divisors: 1, 3, 7, 21
 * 4 has 3 divisors: 1, 2, 4
 * 7 has 2 divisors: 1, 7
 * The answer is the sum of divisors of 21 only.
 */

/*
 * Constraints:
 * 1 <= nums.length <= 10^4
 * 1 <= nums[i] <= 10^5
 */

#include <vector>
#include <numeric>

using namespace std;

class Solution {
public:
    int sumFourDivisors(vector<int>& nums) {
        int result = 0;
        for(int num: nums)
        {
            vector<int> divisors = _solve(num);
            if((int)divisors.size() == 4)
                result += accumulate(divisors.begin(), divisors.end(), 0);
        }
        return result;
    }

private:
    vector<int> _solve(int num)
    {
        vector<int> result;
        for(int i = 1; i * i <= num; ++i)
        {
            int j = num / i;
            if(i * j == num)
            {
                result.push_back(i);
                if(i != j)
                    result.push_back(j);
            }
        }
        return result;
    }
};

#include <cmath>
#include <unordered_map>

class Solution_2 {
public:
    int sumFourDivisors(vector<int>& nums) {
        const int C = 1e5;
        const int C3 = pow(C, (double)1/3);
        vector<int> p1 = get_primes(C);
        int m = p1.size();
        unordered_map<int, int> mapping;
        for(int p: p1)
            if(p <= C3)
                mapping[p * p * p] = 1 + p + p * p + p * p * p;
        for(int i = 1; i < m; ++i)
            for(int j = 0; j < i; ++j)
            {
                if(p1[i] <= C / p1[j] + 1)
                    mapping[p1[i] * p1[j]] = 1 + p1[i] + p1[j] + p1[i] * p1[j];
                else
                    break;
            }
        int ans = 0;
        for(int i: nums)
            if(mapping.count(i) > 0)
                ans += mapping[i];
        return ans;
    }

private:
    vector<int> get_primes(int n) {
        if(n < 2) return {};
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
        vector<int> result;
        for(int i = 0; i < n; ++ i)
        {
            bool flag = vec[i];
            if(flag)
                result.push_back(i);
        }
        return result;
    }
};

