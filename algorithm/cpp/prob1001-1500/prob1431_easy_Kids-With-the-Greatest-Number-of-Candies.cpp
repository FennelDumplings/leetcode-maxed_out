// prob1431: Kids With the Greatest Number of Candies

/*
 * https://leetcode-cn.com/problems/kids-with-the-greatest-number-of-candies/
 */

#include <vector>

using namespace std;

class Solution {
public:
    vector<bool> kidsWithCandies(vector<int>& candies, int extraCandies) {
        int n = candies.size();
        int mx = candies[0];
        for(const int &candie: candies)
            mx = max(mx, candie);
        vector<bool> result(n, false);
        for(int i = 0; i < n; ++i)
            if(extraCandies + candies[i] >= mx)
                result[i] = true;
        return result;
    }
};
