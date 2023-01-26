// prob716: Max Stack

/*
 * https://leetcode-cn.com/problems/max-stack/
 */

#include <vector>
#include <stack>

using namespace std;

class MaxStack_2 {
public:
    /** initialize your data structure here. */
    MaxStack_2() {
        st = stack<int>();
        st_max = stack<int>();
    }

    void push(int x) {
        st.push(x);
        if(st_max.empty() || st_max.top() <= x)
            st_max.push(x);
    }

    int pop() {
        int ans = st.top();
        if(st.top() == st_max.top())
            st_max.pop();
        st.pop();
        return ans;
    }

    int top() {
        return st.top();
    }

    int peekMax() {
        return st_max.top();
    }

    int popMax() {
        stack<int> st_tmp;
        int ans = st_max.top();
        while(st.top() < st_max.top())
        {
            st_tmp.push(st.top());
            st.pop();
        }
        st_max.pop();
        st.pop();
        while(!st_tmp.empty())
        {
            st.push(st_tmp.top());
            if(st_max.empty() || st_tmp.top() >= st_max.top())
                st_max.push(st_tmp.top());
            st_tmp.pop();
        }
        return ans;
    }

private:
    stack<int> st;
    stack<int> st_max;
};

#include <map>
#include <list>

class MaxStack {
public:
    /** initialize your data structure here. */
    MaxStack() {
        l = list<int>();
        mapping = map<int, list<list<int>::iterator>>();
    }

    void push(int x) {
        l.push_back(x);
        mapping[x].push_back(--l.end());
    }

    int pop() {
        int x = l.back();
        l.pop_back();
        mapping[x].pop_back();
        if(mapping[x].empty())
            mapping.erase(x);
        return x;
    }

    int top() {
        return l.back();
    }

    int peekMax() {
        return mapping.rbegin() -> first;
    }

    int popMax() {
        int x = mapping.rbegin() -> first;
        auto it = mapping[x].back();
        l.erase(it);
        mapping[x].pop_back();
        if(mapping[x].empty())
            mapping.erase(x);
        return x;
    }

private:
    list<int> l;
    map<int, list<list<int>::iterator>> mapping;
};
