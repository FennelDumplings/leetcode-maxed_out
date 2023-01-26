// prob370: Range Addition

/*
 * Assume you have an array of length n initialized with all 0's and are given k update operations.
 * Each operation is represented as a triplet: [startIndex, endIndex, inc] which increments each element of subarray A[startIndex ... endIndex] (startIndex and endIndex inclusive) with inc.
 * Return the modified array after all k operations were executed.
 */

/*
 * Example:
 *
 * Input: length = 5, updates = [[1,3,2],[2,4,3],[0,2,-2]]
 * Output: [-2,0,3,5,3]
 * Explanation:
 *
 * Initial state:
 * [0,0,0,0,0]
 *
 * After applying operation [1,3,2]:
 * [0,2,2,2,0]
 *
 * After applying operation [2,4,3]:
 * [0,2,5,5,3]
 *
 * After applying operation [0,2,-2]:
 * [-2,0,3,5,3]
 */

#include <vector>

using namespace std;

class Solution {
public:
    vector<int> getModifiedArray(int length, vector<vector<int>>& updates) {
        int n = length;
        vector<int> diff(n);
        for(const vector<int>& update: updates)
        {
            int s = update[0], e = update[1], i = update[2];
            diff[s] += i;
            if(e + 1 < n)
                diff[e + 1] -= i;
        }
        vector<int> result(n);
        result[0] = diff[0];
        for(int i = 1; i < n; ++i)
        {
            result[i] = result[i - 1] + diff[i];
        }
        return result;
    }
};
