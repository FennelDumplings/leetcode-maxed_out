// prob670: Maximum Swap

/*
 * Given a non-negative integer, you could swap two digits at most once to get the maximum valued number. Return the maximum valued number you could get.
 */

/*
 * Example 1:
 * Input: 2736
 * Output: 7236
 * Explanation: Swap the number 2 and the number 7.
 * Example 2:
 * Input: 9973
 * Output: 9973
 * Explanation: No swap.
 */

/*
 * Note:
 * The given number is in the range [0, 108]
 */

#include <string>
#include <vector>
#include <sstream>

using namespace std;

class Solution {
public:
    int maximumSwap(int num) {
        if(num < 10) return num;
        string num_str = to_string(num);
        int n = num_str.size();
        int iter = 0;
        while(iter < n - 1)
        {
            int cur_high = num_str[iter];
            int maxx = cur_high;
            vector<int> idxs;
            for(int i = iter + 1; i < n; ++i)
            {
                if(num_str[i] > maxx)
                {
                    idxs.clear();
                    maxx = num_str[i];
                    idxs.push_back(i);
                }
                else if(num_str[i] == maxx && maxx > cur_high)
                    idxs.push_back(i);
            }
            if(!idxs.empty())
            {
                swap(num_str[iter], num_str[idxs.back()]);
                break;
            }
            ++iter;
        }
        stringstream ss;
        int result;
        ss << num_str;
        ss >> result;
        return result;
    }
};
