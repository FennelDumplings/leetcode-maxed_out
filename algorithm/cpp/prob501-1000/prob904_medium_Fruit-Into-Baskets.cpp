// prob904: Fruit Into Baskets

/*
 * In a row of trees, the i-th tree produces fruit with type tree[i].
 * You start at any tree of your choice, then repeatedly perform the following steps:
 * Add one piece of fruit from this tree to your baskets.  If you cannot, stop.
 * Move to the next tree to the right of the current tree.  If there is no tree to the right, stop.
 * Note that you do not have any choice after the initial choice of starting tree: you must perform step 1, then step 2, then back to step 1, then step 2, and so on until you stop.
 * You have two baskets, and each basket can carry any quantity of fruit, but you want each basket to only carry one type of fruit each.
 * What is the total amount of fruit you can collect with this procedure?
 */

/*
 * Example 1:
 * Input: [1,2,1]
 * Output: 3
 * Explanation: We can collect [1,2,1].
 * Example 2:
 * Input: [0,1,2,2]
 * Output: 3
 * Explanation: We can collect [1,2,2].
 * If we started at the first tree, we would only collect [0, 1].
 * Example 3:
 * Input: [1,2,3,2,2]
 * Output: 4
 * Explanation: We can collect [2,3,2,2].
 * If we started at the first tree, we would only collect [1, 2].
 * Example 4:
 * Input: [3,3,3,1,2,1,1,2,3,3,4]
 * Output: 5
 * Explanation: We can collect [1,2,1,1,2].
 * If we started at the first tree or the eighth tree, we would only collect 4 fruits.
 */

/*
 * Note:
 * 1 <= tree.length <= 40000
 * 0 <= tree[i] < tree.length
 */

#include <vector>
#include <unordered_map>

using namespace std;

// 哈希表维护双指针内的内容
// 200ms
class Solution {
public:
    int totalFruit(vector<int>& tree) {
        int n = tree.size();
        unordered_map<int, int> mapping;
        int left = 0, right = 0;
        while(right < n)
        {
            auto it = mapping.find(tree[right]);
            if(it != mapping.end())
            {
                ++mapping[tree[right]];
                ++right;
            }
            else if(mapping.size() < 2)
            {
                mapping[tree[right]] = 1;
                ++right;
            }
            else
                break;
        }
        int result = right - left;
        while(right < n)
        {
            while(mapping.size() == 2)
            {
                --mapping[tree[left]];
                if(mapping[tree[left]] == 0)
                    mapping.erase(mapping.find(tree[left]));
                ++left;
            }
            while(right < n)
            {
                auto it = mapping.find(tree[right]);
                if(it != mapping.end())
                {
                    ++mapping[tree[right]];
                    ++right;
                }
                else if(mapping.size() < 2)
                {
                    mapping[tree[right]] = 1;
                    ++right;
                }
                else
                    break;
            }
            result = max(result, right - left);
        }
        return result;
    }
};

// 哈希表中维护数据很小(3以内)用变量和计数器代替哈希表
// 124 ms
class Solution_2 {
public:
    int totalFruit(vector<int>& tree) {
        int n = tree.size();
        int left = 0, right = 0;
        int num1 = -1, count1 = 0;
        int num2 = -1, count2 = 0;
        while(right < n)
        {
            if(tree[right] == num1)
            {
                ++count1;
                ++right;
            }
            else if(tree[right] == num2)
            {
                ++count2;
                ++right;
            }
            else if(num1 == -1)
            {
                num1 = tree[right];
                count1 = 1;
                ++right;
            }
            else if(num2 == -1)
            {
                num2 = tree[right];
                count2 = 1;
                ++right;
            }
            else
                break;
        }
        int result = right - left;
        while(right < n)
        {
            while(num1 != -1 && num2 != -1)
            {
                if(tree[left] == num1)
                {
                    --count1;
                    if(count1 == 0)
                        num1 = -1;
                }
                else if(tree[left] == num2)
                {
                    --count2;
                    if(count2 == 0)
                        num2 = -1;
                }
                ++left;
            }
            while(right < n)
            {
                if(tree[right] == num1)
                {
                    ++count1;
                    ++right;
                }
                else if(tree[right] == num2)
                {
                    ++count2;
                    ++right;
                }
                else if(num1 == -1)
                {
                    num1 = tree[right];
                    count1 = 1;
                    ++right;
                }
                else if(num2 == -1)
                {
                    num2 = tree[right];
                    count2 = 1;
                    ++right;
                }
                else
                    break;
            }
            result = max(result, right - left);
        }
        return result;
    }
};
