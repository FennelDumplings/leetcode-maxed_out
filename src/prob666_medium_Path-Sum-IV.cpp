// prob666: Path Sum IV

/*
 * If the depth of a tree is smaller than 5, then this tree can be represented by a list of three-digits integers.
 * For each integer in this list:
 * The hundreds digit represents the depth D of this node, 1 <= D <= 4.
 * The tens digit represents the position P of this node in the level it belongs to, 1 <= P <= 8. The position is the same as that in a full binary tree.
 * The units digit represents the value V of this node, 0 <= V <= 9.
 * Given a list of ascending three-digits integers representing a binary tree with the depth smaller than 5, you
 * need to return the sum of all paths from the root towards the leaves.
 */

/*
 * Example 1:
 * Input: [113, 215, 221]
 * Output: 12
 * Explanation:
 * The tree that the list represents is:
 *     3
 *    / \
 *   5   1
 * The path sum is (3 + 5) + (3 + 1) = 12.
 * Example 2:
 * Input: [113, 221]
 * Output: 4
 * Explanation:
 * The tree that the list represents is:
 *     3
 *      \
 *       1
 * The path sum is (3 + 1) = 4.
 */

#include <vector>
#include <cmath>

using namespace std;

class Solution {
public:
    int pathSum(vector<int>& nums) {
        if(nums.empty()) return 0;
        vector<int> tree(16, -1);
        int n = nums.size();
        for(int i = 0; i < n; ++i)
        {
            int num = nums[i];
            int val = num % 10;
            num /= 10;
            int col = num % 10;
            num /= 10;
            int row = num % 10;
            int idx = pow(2, row - 1) + col - 1;
            tree[idx] = val;
        }
        int result = 0;
        _proeOrder(tree, 1, 0, result);
        return result;
    }

private:
    void _proeOrder(const vector<int>& tree, int i, int sum, int& result)
    {
        sum += tree[i];
        if(i * 2 > 15 || ((i * 2 + 1 > 15) && tree[i * 2] == -1) || (tree[i * 2] == -1 && tree[i * 2 + 1] == -1))
        {
            result += sum;
            return;
        }

        if(i * 2 <= 15 && tree[i * 2] != -1)
            _proeOrder(tree, i * 2, sum, result);
        if(i * 2 + 1 <= 15 && tree[i * 2 + 1] != -1)
            _proeOrder(tree, i * 2 + 1, sum, result);
    }
};
