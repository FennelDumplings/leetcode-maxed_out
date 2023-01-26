// prob818: Race Car

/*
 * Your car starts at position 0 and speed +1 on an infinite number line.  (Your car can go into negative positions.)
 * Your car drives automatically according to a sequence of instructions A (accelerate) and R (reverse).
 * When you get an instruction "A", your car does the following: position += speed, speed *= 2.
 * When you get an instruction "R", your car does the following: if your speed is positive then speed = -1 , otherwise speed = 1.  (Your position stays the same.)
 * For example, after commands "AAR", your car goes to positions 0->1->3->3, and your speed goes to 1->2->4->-1.
 * Now for some target position, say the length of the shortest sequence of instructions to get there.
 */

/*
 * Example 1:
 * Input:
 * target = 3
 * Output: 2
 * Explanation:
 * The shortest instruction sequence is "AA".
 * Your position goes from 0->1->3.
 * Example 2:
 * Input:
 * target = 6
 * Output: 5
 * Explanation:
 * The shortest instruction sequence is "AAARA".
 * Your position goes from 0->1->3->7->7->6.
 */

/*
 * Note:
 * 1 <= target <= 10000.
 */

#include <vector>
#include <map>
#include <cmath>

using namespace std;

class Solution {
public:
    int racecar(int target) {
        for(int i = 1; pow(2, i - 1) <= 10000; ++i)
            mapping[pow(2, i) - 1] = i;
        int N = (--mapping.end()) -> first;
        vector<int> dp(N + 1, -1);
        dp[1] = 1;
        dp[2] = 4;
        return solve(target, dp);
    }

private:
    map<int, int> mapping;

    int solve(int target, vector<int>& dp)
    {
        if(dp[target] != -1)
            return dp[target];

        int power = get_k(target);
        int k = mapping[power];
        if(target == power)
        {
            dp[target] = solve((target - 1) / 2, dp) + 1;
            return dp[target];
        }
        // 2^(k-1)-1 i < power(2^k-1)
        int prev_power = pow(2, k - 1) - 1;
        int prev_prev_power = pow(2, k - 2) - 1;
        dp[target] = solve(power, dp) + 1 + solve(power - target, dp);
        int item = solve(prev_power, dp) + 1;
        dp[target] = min(dp[target], item + 1 + solve(target - prev_power, dp));
        int i = 0;
        while(true)
        {
            int x = prev_power - (pow(2, i) - 1);
            if(x <= prev_prev_power)
                break;
            int tmp = solve(prev_power - x, dp) + 1;
            tmp += solve(target - x, dp);
            dp[target] = min(dp[target], item + tmp);
            ++i;
        }

        return dp[target];
    }

    int get_k(int i)
    {
        // pow(2, k) - 1 >= i 的最小的 k
        // pow(2, k - 1) < i <= pow(2, k)
        auto it = mapping.lower_bound(i);
        return it -> first;;
    }
};
