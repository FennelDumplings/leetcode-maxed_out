// prob232: Implement Queue using Stacks

/*
 * Implement the following operations of a queue using stacks.
 * push(x) -- Push element x to the back of queue.
 * pop() -- Removes the element from in front of queue.
 * peek() -- Get the front element.
 * empty() -- Return whether the queue is empty.
 */

/*
 * MyQueue queue = new MyQueue();
 * queue.push(1);
 * queue.push(2);
 * queue.peek();  // returns 1
 * queue.pop();   // returns 1
 * queue.empty(); // returns false
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
        if(st_out.empty())
        {
            st_out.push(st_in.top());
            st_in.pop();
        }

    }

    /** Removes the element from in front of queue and returns that element. */
    int pop() {
        int pop_item = st_out.top();
        st_out.pop();
        if(st_out.empty())
        {
            while(!st_in.empty())
            {
                st_out.push(st_in.top());
                st_in.pop();
            }
        }
        return pop_item;
    }

    /** Get the front element. */
    int peek() {
        return st_out.top();
    }

    /** Returns whether the queue is empty. */
    bool empty() {
        return st_out.empty();
    }

private:
    stack<int> st_in;
    stack<int> st_out;
};
