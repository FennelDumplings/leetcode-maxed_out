// interview03.05: 栈排序

/*
 * https://leetcode-cn.com/problems/sort-of-stacks-lcci/
 */

#include <stack>

using namespace std;

class SortedStack {
public:
    SortedStack() {
        st_sort = stack<int>();
        st = stack<int>();
    }

    void push(int val) {
        while(!st_sort.empty() && st_sort.top() < val)
        {
            st.push(st_sort.top());
            st_sort.pop();
        }
        st_sort.push(val);
        while(!st.empty())
        {
            st_sort.push(st.top());
            st.pop();
        }
    }

    void pop() {
        if(isEmpty())
            return;
        st_sort.pop();
    }

    int peek() {
        if(isEmpty())
            return -1;
        int ans = st_sort.top();
        return ans;
    }

    bool isEmpty() {
        return st_sort.empty();
    }

private:
    stack<int> st_sort;
    stack<int> st;
};

// 惰性更新
// 惰性更新其它用处：并查集，线段树
class SortedStack_2 {
public:
    SortedStack_2() {
        st_sort = stack<int>();
        st = stack<int>();
    }

    void push(int val) {
        while(!st_sort.empty() && st_sort.top() < val)
        {
            st.push(st_sort.top());
            st_sort.pop();
        }
        while(!st.empty() && st.top() > val)
        {
            st_sort.push(st.top());
            st.pop();
        }
        st_sort.push(val);
    }

    void pop() {
        if(isEmpty())
            return;
        while(!st.empty())
        {
            st_sort.push(st.top());
            st.pop();
        }
        st_sort.pop();
    }

    int peek() {
        if(isEmpty())
            return -1;
        while(!st.empty())
        {
            st_sort.push(st.top());
            st.pop();
        }
        int ans = st_sort.top();
        return ans;
    }

    bool isEmpty() {
        return st_sort.empty() && st.empty();
    }

private:
    stack<int> st_sort;
    stack<int> st;
};
