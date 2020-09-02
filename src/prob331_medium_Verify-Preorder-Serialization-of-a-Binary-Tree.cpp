// prob331: Verify Preorder Serialization of a Binary Tree

/*
 * https://leetcode-cn.com/problems/verify-preorder-serialization-of-a-binary-tree/
 */

#include <string>
#include <stack>

using namespace std;

class Solution {
public:
    bool isValidSerialization(string preorder) {
        if(preorder.empty())
            return false;
        if(preorder == "#")
            return true;
        int n = preorder.size();
        int iter = 0;
        while(iter < n && preorder[iter] != ',')
            ++iter;
        string cur = preorder.substr(0, iter);
        if(cur == "#")
            return iter == n;
        stack<int> st;
        st.push(2);
        ++iter;
        while(!st.empty() && iter < n)
        {
            int right = iter;
            while(right < n && preorder[right] != ',')
                ++right;
            string cur = preorder.substr(iter, right - iter);
            if(cur == "#")
            {
                --st.top();
                while(!st.empty() && st.top() == 0)
                {
                    st.pop();
                    if(!st.empty())
                        --st.top();
                }
            }
            else
            {
                st.push(2);
            }
            iter = right + 1;
        }
        return st.empty() && iter == n;
    }
};
