// interview03.04: 化栈为队

/*
 * https://leetcode-cn.com/problems/implement-queue-using-stacks-lcci/
 */

#include <stack>

using namespace std;

class MyQueue {
public:
    /** Initialize your data structure here. */
    MyQueue() {
        st_in = stack<int>();
        st_out = stack<int>();
    }

    /** Push element x to the back of queue. */
    void push(int x) {
        st_in.push(x);
    }

    /** Removes the element from in front of queue and returns that element. */
    int pop() {
        if(st_out.empty())
        {
            while(!st_in.empty())
            {
                st_out.push(st_in.top());
                st_in.pop();
            }
        }
        if(st_out.empty()) return -1;
        int ans = st_out.top();
        st_out.pop();
        return ans;
    }

    /** Get the front element. */
    int peek() {
        if(st_out.empty())
        {
            while(!st_in.empty())
            {
                st_out.push(st_in.top());
                st_in.pop();
            }
        }
        if(st_out.empty()) return -1;
        return st_out.top();
    }

    /** Returns whether the queue is empty. */
    bool empty() {
        return st_out.empty() && st_in.empty();
    }

private:
    stack<int> st_in, st_out;
};
