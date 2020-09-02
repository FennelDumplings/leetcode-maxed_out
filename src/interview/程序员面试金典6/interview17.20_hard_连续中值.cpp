// interview17.20: 连续中值

/*
 * https://leetcode-cn.com/problems/continuous-median-lcci/
 */

#include <queue>

using namespace std;

class MedianFinder {
public:
    /** initialize your data structure here. */
    MedianFinder() {
        pq_left = priority_queue<int>(); // 大顶堆
        pq_right = priority_queue<int, vector<int>, greater<int> >(); // 小顶堆
    }

    void addNum(int num) {
        if(pq_right.size() == 0)
        {
            pq_right.push(num);
            return;
        }
        // double cur_median = findMedian();
        // if((double)num >= cur_median)
        if(num >= pq_right.top())
            pq_right.push(num);
        else
            pq_left.push(num);
        if(pq_left.size() > pq_right.size())
        {
            int top = pq_left.top();
            pq_left.pop();
            pq_right.push(top);
        }
        if(pq_left.size() + 1 < pq_right.size())
        {
            int top = pq_right.top();
            pq_right.pop();
            pq_left.push(top);
        }
    }

    double findMedian() {
        if(pq_right.size() == 0)
            return 0.0;
        if((pq_left.size() + pq_right.size()) % 2 == 1)
            return (double)pq_right.top();
        else
            return (pq_right.top() + pq_left.top()) / 2.0;
    }

private:
    priority_queue<int> pq_left; // 大顶堆
    priority_queue<int, vector<int>, greater<int> > pq_right; // 小顶堆
};
