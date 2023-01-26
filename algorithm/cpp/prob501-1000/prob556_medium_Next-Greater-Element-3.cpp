// prob556: Next Greater Element III

/*
 * https://leetcode-cn.com/problems/next-greater-element-iii/
 */

#include <stack>
#include <climits>

using namespace std;

class Solution {
public:
    int nextGreaterElement(int n) {
        using ll = long long;
        stack<int> st;
        while(n)
        {
            int d = n % 10;
            n /= 10;
            if(st.empty() || st.top() <= d)
                st.push(d);
            else
            {
                // 找到更换数字的最高位
                // 把更高位的数字平移到 ans 中
                ll ans = n;
                stack<int> st_append;
                // i 这位要放栈里比 i 大的最小的数
                // d 以及栈里其它的数字按升序放入
                while(!st.empty() && st.top() > d)
                {
                    st_append.push(st.top());
                    st.pop();
                }
                ans *= 10;
                ans += st_append.top();
                st_append.pop();
                st_append.push(d);
                while(!st.empty())
                {
                    st_append.push(st.top());
                    st.pop();
                }
                // 把 st_append 中的数字倒进 ans
                while(!st_append.empty())
                {
                    ans *= 10;
                    ans += st_append.top();
                    st_append.pop();
                }
                if(ans > INT_MAX)
                    return -1;
                return ans;
            }
        }
        return -1;
    }
};
