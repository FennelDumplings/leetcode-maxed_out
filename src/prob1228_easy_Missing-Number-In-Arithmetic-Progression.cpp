// prob1228: Missing Number In Arithmetic Progression

/*
 * In some array arr, the values were in arithmetic progression: the values arr[i+1] - arr[i] are all equal for every 0 <= i < arr.length - 1.
 * Then, a value from arr was removed that was not the first or last value in the array.
 * Return the removed value.
 */

/*
 * Example 1:
 * Input: arr = [5,7,11,13]
 * Output: 9
 * Explanation: The previous array was [5,7,9,11,13].
 * Example 2:
 * Input: arr = [15,13,12]
 * Output: 14
 * Explanation: The previous array was [15,14,13,12].
 */

/*
 * Constraints:
 * 3 <= arr.length <= 1000
 * 0 <= arr[i] <= 10^5
 */

#include <vector>

using namespace std;

class Solution {
public:
    int missingNumber(vector<int>& arr) {
        int n = arr.size();
        int d = (arr.back() - arr.front()) / n;
        int iter = arr[0];
        for(int i = 1; i < n - 1; ++i)
        {
            iter += d;
            if(iter != arr[i])
                return iter;
        }
        return iter + d;
    }
};
