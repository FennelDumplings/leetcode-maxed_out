// prob1151: Minimum Swaps to Group All 1's Together

/*
 * Given a binary array data, return the minimum number of swaps required to group all 1’s present in the array together in any place in the array.
 */

/*
 * Example 1:
 * Input: [1,0,1,0,1]
 * Output: 1
 * Explanation:
 * There are 3 ways to group all 1's together:
 * [1,1,1,0,0] using 1 swap.
 * [0,1,1,1,0] using 2 swaps.
 * [0,0,1,1,1] using 1 swap.
 * The minimum is 1.
 * Example 2:
 * Input: [0,0,0,1,0]
 * Output: 0
 * Explanation:
 * Since there is only one 1 in the array, no swaps needed.
 * Example 3:
 * Input: [1,0,1,0,1,0,0,1,1,0,1]
 * Output: 3
 * Explanation:
 * One possible solution that uses 3 swaps is [0,0,0,0,0,1,1,1,1,1,1].
 */

/*
 * Note:
 * 1 <= data.length <= 10^5
 * 0 <= data[i] <= 1
 */

#include <vector>

using namespace std;

class Solution {
public:
    int minSwaps(vector<int>& data) {
        int n1 = 0;
        for(int i: data)
            if(i == 1)
                ++n1;
        if(n1 <= 1) return  0;
        int n = data.size();
        int n0 = 0;
        for(int right = 0; right < n1; ++right)
            if(data[right] == 0)
                ++n0;
        int result = n0;
        for(int right = n1; right < n; ++right)
        {
            if(data[right] == 0 && data[right - n1] == 1)
                ++n0;
            else if(data[right] == 1 && data[right - n1] == 0)
                --n0;
            result = min(result, n0);
        }
        return result;
    }
};
