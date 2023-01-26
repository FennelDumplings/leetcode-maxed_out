// prob605: Can Place Flowers

/*
 * Suppose you have a long flowerbed in which some of the plots are planted and some are not. However, flowers cannot be planted in adjacent plots - they would compete for water and both would die.
 *
 * Given a flowerbed (represented as an array containing 0 and 1, where 0 means empty and 1 means not empty), and a number n, return if n new flowers can be planted in it without violating the no-adjacent-flowers rule.
 */

/*
 * Example 1:
 * Input: flowerbed = [1,0,0,0,1], n = 1
 * Output: True
 * Example 2:
 * Input: flowerbed = [1,0,0,0,1], n = 2
 * Output: False
 */

/*
 * Note:
 * The input array won't violate no-adjacent-flowers rule.
 * The input array size is in the range of [1, 20000].
 * n is a non-negative integer which won't exceed the input array size.
 */

#include <vector>

using namespace std;

class Solution {
public:
    bool canPlaceFlowers(vector<int>& flowerbed, int n) {
        int N = flowerbed.size();
        int maxx = 0;
        int left = 0;
        while(left < N)
        {
            while(left < N && flowerbed[left] == 1)
                ++left;
            int right = left + 1;
            while(right < N && flowerbed[right] == 0)
                ++right;
            int len = right - left;
            if(right < N)
                --len;
            if(left > 0)
                --len;
            maxx += (len + 1) / 2;
            left = right;
        }
        return maxx >= n;
    }
};
