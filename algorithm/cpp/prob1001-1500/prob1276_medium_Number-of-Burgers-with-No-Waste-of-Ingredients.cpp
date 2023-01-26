// prob1276: Number of Burgers with No Waste of Ingredients

/*
 * https://leetcode-cn.com/problems/number-of-burgers-with-no-waste-of-ingredients/
 */

#include <vector>

using namespace std;

class Solution {
public:
    vector<int> numOfBurgers(int tomatoSlices, int cheeseSlices) {
        int a = tomatoSlices, b = cheeseSlices;
        if(a & 1)
            return {};
        if(a / 2 - b < 0 || b * 2 - a / 2 < 0)
            return {};
        return {a / 2 - b, b * 2 - a / 2};
    }
};
