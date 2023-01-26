// interview33: 二叉搜索树的后序遍历序列

/*
 * https://leetcode-cn.com/problems/er-cha-sou-suo-shu-de-hou-xu-bian-li-xu-lie-lcof/
 */

#include <vector>
#include <stack>
#include <climits>

using namespace std;

class Solution {
public:
    bool verifyPostorder(vector<int>& postorder) {
        // 不能有 312 模式
        int n = postorder.size();
        if(n <= 2) return true;
        int sub_minx = INT_MAX;
        stack<int> st;
        for(int i = n - 1; i >= 0; --i)
        {
            if(postorder[i] > sub_minx)
                return false;
            while(!st.empty() && st.top() > postorder[i])
            {
                sub_minx = min(sub_minx, st.top());
                st.pop();
            }
            st.push(postorder[i]);
        }
        return true;
    }
};
