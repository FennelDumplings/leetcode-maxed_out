// interview41: 数据流中的中位数

/*
 * https://leetcode-cn.com/problems/shu-ju-liu-zhong-de-zhong-wei-shu-lcof/
 */

#include <queue>

using namespace std;

class MedianFinder {
public:
    /** initialize your data structure here. */
    MedianFinder() {
        pq_left = priority_queue<int>();
        pq_right = priority_queue<int, vector<int>, greater<int>>();
    }

    void addNum(int num) {
        if(pq_left.size() == pq_right.size())
            pq_left.push(num);
        else
            pq_right.push(num);
        if(!pq_left.empty() && !pq_right.empty() && pq_left.top() > pq_right.top())
        {
            int top_left = pq_left.top();
            int top_right = pq_right.top();
            pq_left.pop();
            pq_right.pop();
            pq_left.push(top_right);
            pq_right.push(top_left);
        }
    }

    double findMedian() {
        if(pq_left.size() == pq_right.size())
            return ((double)pq_left.top() + pq_right.top()) / 2;
        else
            return (double)pq_left.top();
    }

private:
    priority_queue<int> pq_left;
    priority_queue<int, vector<int>, greater<int>> pq_right;
};
