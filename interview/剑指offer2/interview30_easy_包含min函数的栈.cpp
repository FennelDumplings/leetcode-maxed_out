// interview30: 包含min函数的栈

/*
 * https://leetcode-cn.com/problems/bao-han-minhan-shu-de-zhan-lcof/
 */

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
        if(st_min.empty() || x <= st_min.top())
            st_min.push(x);
    }

    void pop() {
        if(st.top() == st_min.top())
            st_min.pop();
        st.pop();
    }

    int top() {
        return st.top();
    }

    int min() {
        return st_min.top();
    }

private:
    stack<int> st;
    stack<int> st_min;
};
