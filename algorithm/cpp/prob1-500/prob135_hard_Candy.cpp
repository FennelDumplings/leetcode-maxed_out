// porb135: Candy

/*
 * There are N children standing in a line. Each child is assigned a rating value.
 * You are giving candies to these children subjected to the following requirements:
 * Each child must have at least one candy.
 * Children with a higher rating get more candies than their neighbors.
 * What is the minimum candies you must give?
 */

/*
 * Example 1:
 * Input: [1,0,2]
 * Output: 5
 * Explanation: You can allocate to the first, second and third child with 2, 1, 2 candies respectively.
 * Example 2:
 * Input: [1,2,2]
 * Output: 4
 * Explanation: You can allocate to the first, second and third child with 1, 2, 1 candies respectively.
 *              The third child gets 1 candy because it satisfies the above two conditions.
 */

#include <vector>

using namespace std;

class Solution_2 {
public:
    int candy(vector<int>& ratings) {
        int result = 0;
        int n = ratings.size();
        int i = 0, public_valley = 0;
        while(i < n)
        {
            int j = i + 1;
            // 确定波峰，up, down 代表坡长度，均包含波峰点，因此长度至少为 1
            while(j < n && ratings[j - 1] < ratings[j])
                ++j;
            int peak = j;
            int up = j - i;
            // 确定波谷
            while(j < n && ratings[j - 1] > ratings[j])
                ++j;
            int down = j - peak + 1;
            if(up < down)
                swap(up, down);
            // 计算这一趟波峰波谷需要的糖果数量，波峰的糖果数量与上坡下坡较长的长度有关
            // 因此将波峰归到最长的一个坡
            // 已处理成 up >= down
            result += (up * (up + 1) / 2 + (down - 1) * down / 2);

            // 准备下一个波峰波谷
            // 如果是一段平的，即不存在坡，则 ++i，否则波谷会被下一个波峰波谷公用为起点，
            // 所以会在下一次的分配中再次被分配一个糖果，记录下公用的波谷数量
            if(j == i + 1)
                ++i;
            else
            {
                i = j - 1;
                public_valley += 1;
            }
        }
        return result - public_valley;
    }
};
