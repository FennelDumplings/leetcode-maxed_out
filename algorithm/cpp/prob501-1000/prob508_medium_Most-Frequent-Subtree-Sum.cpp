// prob508: Most Frequent Subtree Sum

/*
 * Given the root of a tree, you are asked to find the most frequent subtree sum. The subtree sum of a node is defined
 * as the sum of all the node values formed by the subtree rooted at that node (including the node itself). So what is
 * the most frequent subtree sum value? If there is a tie, return all the values with the highest frequency in any order.
 */

/*
 * Examples 1
 * Input:
 *   5
 *  /  \
 * 2   -3
 * return [2, -3, 4], since all the values happen only once, return all of them in any order.
 * Examples 2
 * Input:
 *   5
 *  /  \
 * 2   -5
 * return [2], since 2 happens twice, however -5 only occur once.
 */

/*
 * Note: You may assume the sum of values in any subtree is in the range of 32-bit signed integer.
 */

#include <vector>
#include <unordered_map>
#include "include/Node.h"

using namespace std;

class Solution {
public:
    vector<int> findFrequentTreeSum(TreeNode* root) {
        if(!root) return vector<int>();
        unordered_map<int, int> mapping;
        _postOrder(root, mapping);
        int cnt = 0;
        vector<int> result;
        for(auto it = mapping.begin(); it != mapping.end(); ++it)
        {
            if(cnt < it -> second)
            {
                result.clear();
                result.push_back(it -> first);
                cnt = it -> second;
            }
            else if(cnt == it -> second)
                result.push_back(it -> first);
        }
        return result;
    }

private:
    int _postOrder(TreeNode* root, unordered_map<int, int>& mapping)
    {
        int left_sum = 0, right_sum = 0;
        if(root -> left)
            left_sum = _postOrder(root -> left, mapping);
        if(root -> right)
            right_sum = _postOrder(root -> right, mapping);

        int cur_sum = left_sum + right_sum + root -> val;
        ++mapping[cur_sum];
        return cur_sum;
    }
};
