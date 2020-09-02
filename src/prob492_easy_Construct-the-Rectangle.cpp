// prob492: Construct the Rectangle

/*
 * https://leetcode-cn.com/problems/construct-the-rectangle/
 */

#include <vector>

using namespace std;

class Solution {
public:
    vector<int> constructRectangle(int area) {
        vector<int> result(2, -1);
        int &L = result[0], &W = result[1];
        L = area, W = 1;
        for(int i = 2; i * i <= area; ++i)
        {
            if(area % i == 0)
            {
                W = i;
                L = area / i;
            }
        }
        return result;
    }
};
