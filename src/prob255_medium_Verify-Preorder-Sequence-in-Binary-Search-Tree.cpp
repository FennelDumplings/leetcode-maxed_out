// prob255: Verify Preorder Sequence in Binary Search Tree

/*
 * iven an array of numbers, verify whether it is the correct preorder traversal sequence of a binary search tree.
 * You may assume each number in the sequence is unique.
 */

/*
 * Consider the following binary search tree: 
 *      5
 *     / \
 *    2   6
 *   / \
 *  1   3
 * Example 1:
 * Input: [5,2,6,1,3]
 * Output: false
 * Example 2:
 * Input: [5,2,1,3,6]
 * Output: true
 */

/*
 * Follow up:
 * Could you do it using only constant space complexity
 */

#include <vector>

using namespace std;

class Solution {
public:
    bool verifyPreorder(vector<int>& preorder) {
        if(preorder.empty()) return true;
        int n = preorder.size();
        if(n <= 2) return true;
        // n = 3 时，[2, 3, 1] 是不满足的情况
        int minx1 = preorder[0];
        int i = 1;
        while(i < n && preorder[i] < minx1)
            ++i;
        if(i == n) return true;
        int minx2 = preorder[i];
        // [minx1, +inf) 合法，minx1 < minx2
        ++i;
        while(i < n)
        {
            if(preorder[i] < minx1)
                return false;
            if(preorder[i] > minx2)
            {
                minx1 = minx2;
                minx2 = preorder[i];
            }
            ++i;
        }
        return true;
    }
};
