// interview31: 栈的压入、弹出序列

/*
 * https://leetcode-cn.com/problems/zhan-de-ya-ru-dan-chu-xu-lie-lcof/
 */

#include <vector>
#include <stack>
#include <climits>

using namespace std;

class Solution {
public:
    bool validateStackSequences(vector<int>& pushed, vector<int>& popped) {
        int n = pushed.size();
        if(n <= 2) return true;
        vector<int> mapping(1001, -1);
        for(int i = 0; i < n; ++i)
        {
            mapping[pushed[i]] = i;
        }
        vector<int> seq(n, -1);
        for(int i = 0; i < n; ++i)
        {
            seq[i] = mapping[popped[i]];
        }
        // 判断 seq 中是否有 312 模式
        stack<int> st;
        int sub_minx = INT_MAX;
        for(int i = n - 1; i >= 0; --i)
        {
            if(seq[i] > sub_minx)
                return false;
            while(!st.empty() && st.top() > seq[i])
            {
                sub_minx = min(sub_minx, st.top());
                st.pop();
            }
            st.push(seq[i]);
        }
        return true;
    }
};
