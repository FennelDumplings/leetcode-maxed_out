// interview03.03: 堆盘子

/*
 * https://leetcode-cn.com/problems/stack-of-plates-lcci/
 */

#include <stack>
#include <map>

using namespace std;

class StackOfPlates_2 {
public:
    StackOfPlates_2(int cap) {
        this -> cap = cap;
        stacks = map<int, stack<int>>();
    }

    void push(int val) {
        if(cap == 0) return;
        int tail_idx;
        if(stacks.empty())
        {
            stacks[0] = stack<int>();
            tail_idx = 0;
        }
        else
        {
            PIS tail = *stacks.rbegin();
            tail_idx = tail.first;
        }
        if((int)stacks[tail_idx].size() == cap)
        {
            stacks[tail_idx + 1] = stack<int>();
            ++tail_idx;
        }
        stacks[tail_idx].push(val);
    }

    int pop() {
        if(cap == 0) return -1;
        if(stacks.empty()) return -1;
        PIS tail = *stacks.rbegin();
        int tail_idx = tail.first;
        int ans = stacks[tail_idx].top();
        stacks[tail_idx].pop();
        if(stacks[tail_idx].empty())
        {
            stacks.erase(stacks.find(tail_idx));
            map<int, stack<int>> new_stacks;
            int i = 0;
            for(const auto &item: stacks)
            {
                new_stacks[i] = item.second;
                ++i;
            }
            stacks = new_stacks;
        }
        return ans;
    }

    int popAt(int index) {
        if(cap == 0) return -1;
        if(stacks.count(index) == 0) return -1;
        int ans = stacks[index].top();
        stacks[index].pop();
        if(stacks[index].empty())
        {
            stacks.erase(stacks.find(index));
            map<int, stack<int>> new_stacks;
            int i = 0;
            for(const auto &item: stacks)
            {
                new_stacks[i] = item.second;
                ++i;
            }
            stacks = new_stacks;
        }
        return ans;
    }

private:
    int cap;
    using PIS = pair<int, stack<int>>;
    map<int, stack<int>> stacks;
};


//
#include <set>
#include <vector>
#include <iterator>

class StackOfPlates_3 {
public:
    StackOfPlates_3(int cap) {
        this -> cap = cap;
        stacks = vector<stack<int>>();
    }

    void push(int val) {
        if(cap == 0) return;
        if(stacks.empty())
        {
            stacks.push_back(stack<int>());
        }
        if((int)stacks.back().size() == cap)
        {
            stacks.push_back(stack<int>());
        }
        stack<int> &tail = stacks.back();
        tail.push(val);
    }

    int pop() {
        if(cap == 0) return -1;
        if(stacks.empty()) return -1;
        stack<int> &tail = stacks.back();
        int ans = tail.top();
        tail.pop();
        if(tail.empty())
            stacks.pop_back();
        return ans;
    }

    int popAt(int index) {
        if(cap == 0) return -1;
        if(index >= (int)stacks.size()) return -1;
        auto it = stacks.begin() + index;
        int ans = it -> top();
        it -> pop();
        if(it -> empty())
        {
            stacks.erase(it);
        }
        return ans;
    }

private:
    int cap;
    vector<stack<int>> stacks;
};

#include <list>

class StackOfPlates_4 {
public:
    StackOfPlates_4(int cap) {
        this -> cap = cap;
        stacks = list<stack<int>>();
    }

    void push(int val) {
        if(cap == 0) return;
        if(stacks.empty())
        {
            stacks.push_back(stack<int>());
        }
        if((int)stacks.back().size() == cap)
        {
            stacks.push_back(stack<int>());
        }
        stack<int> &tail = stacks.back();
        tail.push(val);
    }

    int pop() {
        if(cap == 0) return -1;
        if(stacks.empty()) return -1;
        stack<int> &tail = stacks.back();
        int ans = tail.top();
        tail.pop();
        if(tail.empty())
            stacks.pop_back();
        return ans;
    }

    int popAt(int index) {
        if(cap == 0) return -1;
        if(index >= (int)stacks.size()) return -1;
        auto it = stacks.begin();
        advance(it, index);
        int ans = it -> top();
        it -> pop();
        if(it -> empty())
        {
            stacks.erase(it);
        }
        return ans;
    }

private:
    int cap;
    list<stack<int>> stacks;
};

#include <deque>

class StackOfPlates {
public:
    StackOfPlates(int cap) {
        this -> cap = cap;
        stacks = deque<stack<int>>();
    }

    void push(int val) {
        if(cap == 0) return;
        if(stacks.empty())
        {
            stacks.push_back(stack<int>());
        }
        if((int)stacks.back().size() == cap)
        {
            stacks.push_back(stack<int>());
        }
        stack<int> &tail = stacks.back();
        tail.push(val);
    }

    int pop() {
        if(cap == 0) return -1;
        if(stacks.empty()) return -1;
        stack<int> &tail = stacks.back();
        int ans = tail.top();
        tail.pop();
        if(tail.empty())
            stacks.pop_back();
        return ans;
    }

    int popAt(int index) {
        if(cap == 0) return -1;
        if(index >= (int)stacks.size()) return -1;
        auto it = stacks.begin() + index;
        int ans = it -> top();
        it -> pop();
        if(it -> empty())
        {
            stacks.erase(it);
        }
        return ans;
    }

private:
    int cap;
    deque<stack<int>> stacks;
};

