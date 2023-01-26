// prob202: Happy Number

/*
 * Write an algorithm to determine if a number is "happy".
 * A happy number is a number defined by the following process: Starting with any positive integer,
 * replace the number by the sum of the squares of its digits, and repeat the process until the number equals 1 (where it will stay),
 * or it loops endlessly in a cycle which does not include 1. Those numbers for which this process ends in 1 are happy numbers.
 */

/*
 * Example:
 * Input: 19
 * Output: true
 * Explanation:
 * 12 + 92 = 82
 * 82 + 22 = 68
 * 62 + 82 = 100
 * 12 + 02 + 02 = 1
 */

#include <unordered_set>

using namespace std;

// 法一 哈希表
class Solution {
public:
    bool isHappy(int n) {
        unordered_set<int> setting;
        while(n != 1)
        {
            n = _square_sum(n);
            if(setting.find(n) != setting.end())
                return false;
            setting.insert(n);
        }
        return true;
    }

private:
    int _square_sum(int n)
    {
        int result = 0;
        while(n != 0)
        {
            result += (n % 10) * (n % 10);
            n /= 10;
        }
        return result;
    }
};

// 法二：快慢指针思想
class Solution_2 {
public:
    bool isHappy(int n) {
        int n_fast = n, n_slow = n;
        while(n_slow != 1 && n_fast != 1 && _square_sum(n_fast) != 1)
        {
            n_fast = _square_sum(n_fast);
            n_fast = _square_sum(n_fast);
            n_slow = _square_sum(n_slow);
            if(n_slow == n_fast)
                return false;
        }
        return true;
    }

private:
    int _square_sum(int n)
    {
        int result = 0;
        while(n != 0)
        {
            result += (n % 10) * (n % 10);
            n /= 10;
        }
        return result;
    }
};
