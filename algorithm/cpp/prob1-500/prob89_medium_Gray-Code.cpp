// prob89: Gray Code

/*
 * The gray code is a binary numeral system where two successive values differ in only one bit.
 * Given a non-negative integer n representing the total number of bits in the code, print the sequence of gray code.
 * A gray code sequence must begin with 0.
 */

#include <vector>

using namespace std;

class Solution {
public:
    vector<int> grayCode(int n) {
        if(n == 0) return vector<int>({0});
        vector<int> result({0, 1});
        for(int i = 2; i <= n; ++i)
        {
            int m = result.size();
            for(int j = m - 1; j >= 0; --j)
                result.push_back(result[j] + (1 << (i - 1)));
        }
        return result;
    }
};
