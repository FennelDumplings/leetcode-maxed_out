// prob118: Pascal's Triangle

/*
 * Given a non-negative integer numRows, generate the first numRows of Pascal's triangle.
 */

/*
 * Example:
 * Input: 5
 * Output:
 * [
 *      [1],
 *     [1,1],
 *    [1,2,1],
 *   [1,3,3,1],
 *  [1,4,6,4,1]
 * ]
 */

#include <vector>

using namespace std;

class Solution {
public:
    vector<vector<int> > generate(int numRows) {
        if(numRows == 0) return vector<vector<int> >();
        if(numRows == 1) return vector<vector<int> >(1, vector<int>(1, 1));
        vector<vector<int> > result(numRows);
        result[0] = vector<int>(1, 1);
        result[1] = vector<int>(2, 1);
        for(int i = 2; i < numRows; ++i)
        {
            int n = i + 1;
            vector<int> item(n, 1);
            for(int j = 1; j < n - 1; ++j)
                item[j] = result[i - 1][j] + result[i - 1][j - 1];
            result[i] = item;
        }
        return result;
    }
};
