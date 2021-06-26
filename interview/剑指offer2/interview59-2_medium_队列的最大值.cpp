// interview59-2: 队列的最大值

/*
 * https://leetcode-cn.com/problems/dui-lie-de-zui-da-zhi-lcof/
 */

#include <vector>
#include <deque>
#include <queue>

using namespace std;

class MaxQueue {
public:
    MaxQueue() {
        q = queue<int>();
        mq = deque<int>();
    }

    int max_value() {
        if(q.empty()) return -1;
        return mq.front();
    }

    void push_back(int value) {
        q.push(value);
        while(!mq.empty() && mq.back() < value)
            mq.pop_back();
        mq.push_back(value);
    }

    int pop_front() {
        if(q.empty()) return -1;
        int ans = q.front();
        q.pop();
        if(!mq.empty() && mq.front() == ans)
            mq.pop_front();
        return ans;
    }

private:
    queue<int> q;
    deque<int> mq;
};
