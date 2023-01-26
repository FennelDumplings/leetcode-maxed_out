// interview03.02: 栈的最小值

/*
 * https://leetcode-cn.com/problems/min-stack-lcci/
 */

#include <vector>
#include <stack>

using namespace std;

class MinStack {
public:
    /** initialize your data structure here. */
    MinStack() {
        st = stack<int>();
        st_min = stack<int>();
    }

    void push(int x) {
        st.push(x);
        if(st_min.empty() || st_min.top() >= x)
            st_min.push(x);
    }

    void pop() {
        if(st.empty()) return;
        int x = st.top();
        st.pop();
        if(x == st_min.top())
            st_min.pop();
    }

    int top() {
        int x = st.top();
        return x;
    }

    int getMin() {
        if(st.empty()) return -1;
        int minx = st_min.top();
        return minx;
    }

private:
    stack<int> st, st_min;
};
