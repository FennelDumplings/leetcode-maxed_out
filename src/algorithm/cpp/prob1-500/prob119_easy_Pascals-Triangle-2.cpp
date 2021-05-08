// prob119: Pascal's Triangle II

/*
 * Given a non-negative index k where k ≤ 33, return the kth index row of the Pascal's triangle.
 * Note that the row index starts from 0.
 */

/*
 * Example:
 * Input: 3
 * Output: [1,3,3,1]
 */

#include <vector>

using namespace std;

class Solution {
public:
    vector<int> getRow(int rowIndex) {
        if(rowIndex == 0) return vector<int>(1, 1);
        if(rowIndex == 1) return vector<int>(2, 1);
        int n = rowIndex + 1;
        vector<int> result(n, 1);
        for(int i = 2; i <= rowIndex; ++i)
        {
            for(int j = i - 1; j >= 1; --j)
                result[j] = result[j] + result[j - 1];
        }
        return result;
    }
};
