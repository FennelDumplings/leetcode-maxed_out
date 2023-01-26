// prob155: Min Stack

/*
 * Design a stack that supports push, pop, top, and retrieving the minimum element in constant time.
 * push(x) -- Push element x onto stack.
 * pop() -- Removes the element on top of the stack.
 * top() -- Get the top element.
 * getMin() -- Retrieve the minimum element in the stack.
 */

/*
 * MinStack minStack = new MinStack();
 * minStack.push(-2);
 * minStack.push(0);
 * minStack.push(-3);
 * minStack.getMin();   --> Returns -3.
 * minStack.pop();
 * minStack.top();      --> Returns 0.
 * minStack.getMin();   --> Returns -2.
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
        int top_item = st.top();
        st.pop();
        if(top_item == st_min.top())
            st_min.pop();
    }

    int top() {
        return st.top();
    }

    int getMin() {
        return st_min.top();
    }

private:
    stack<int> st;
    stack<int> st_min;
};

int main()
{
    MinStack minStack;
    minStack.push(-2);
    minStack.push(0);
    minStack.push(-3);
    minStack.getMin();
    minStack.pop();
    minStack.top();
    minStack.getMin();
}
