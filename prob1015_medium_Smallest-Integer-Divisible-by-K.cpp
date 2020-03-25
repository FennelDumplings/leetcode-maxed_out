// prob1015: Smallest Integer Divisible by K

/*
 * Given a positive integer K, you need find the smallest positive integer N such that N is divisible by K, and N only contains the digit 1.
 * Return the length of N.  If there is no such N, return -1.
 */

/*
 * Note:
 * 1 <= K <= 10^5
 */

/*
 * Example 1:
 * Input: 1
 * Output: 1
 * Explanation: The smallest answer is N = 1, which has length 1.
 * Example 2:
 * Input: 2
 * Output: -1
 * Explanation: There is no such positive integer N divisible by 2.
 * Example 3:
 * Input: 3
 * Output: 3
 * Explanation: The smallest answer is N = 111, which has length 3.
 */

#include <vector>
#include <unordered_set>

using namespace std;

class Solution {
public:
    int smallestRepunitDivByK(int K) {
        if(K == 1) return 1;

        unordered_set<int> setting;
        int c = 1 % K;
        int result = 1;
        while(c != 0)
        {
            if(setting.find(c) != setting.end())
                return -1;
            setting.insert(c);
            ++result;
            c = (c * 10 + 1) % K;
        }
        return result;
    }
};

// vector 代替哈希表
class Solution_2 {
public:
    int smallestRepunitDivByK(int K) {
        if(K == 1) return 1;

        vector<bool> setting(K, false);
        int c = 1 % K;
        int result = 1;
        while(c != 0)
        {
            if(setting[c])
                return -1;
            setting[c] = true;
            ++result;
            c = (c * 10 + 1) % K;
        }
        return result;
    }
};
