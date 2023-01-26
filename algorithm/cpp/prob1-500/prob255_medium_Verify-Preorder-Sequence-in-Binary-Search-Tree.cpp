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
#include <algorithm>
#include <stack>
#include <climits>

using namespace std;

// 分析问题本质：寻找 132 模式
class Solution_2 {
public:
    bool verifyPreorder(vector<int>& preorder) {
        reverse(preorder.begin(), preorder.end());
        return !find132pattern(preorder);
    }

private:
    bool find132pattern(vector<int>& nums) {
        int n = nums.size();
        if(n < 3) return false;
        stack<int> st;
        int s3 = INT_MIN;
        for(int i = n - 1; i >= 0; --i)
        {
            if(nums[i] < s3) return true;
            while(!st.empty() && st.top() < nums[i])
            {
                s3 = max(s3, st.top());
                st.pop();
            }
            st.push(nums[i]);
        }
        return false;
    }
};
