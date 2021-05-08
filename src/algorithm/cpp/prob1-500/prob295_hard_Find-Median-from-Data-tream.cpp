// prob295: Find Median from Data Stream

/*
 * Median is the middle value in an ordered integer list. If the size of the list is even, there is no middle value. So the median is the mean of the two middle value.
 * For example,
 * [2,3,4], the median is 3
 * [2,3], the median is (2 + 3) / 2 = 2.5
 * Design a data structure that supports the following two operations:
 * void addNum(int num) - Add a integer number from the data stream to the data structure.
 * double findMedian() - Return the median of all elements so far.
 */

/*
 * Example:
 * addNum(1)
 * addNum(2)
 * findMedian() -> 1.5
 * addNum(3)
 * findMedian() -> 2
 */

/* Follow Up
 * If all integer numbers from the stream are between 0 and 100, how would you optimize it?
 * If 99% of all integer numbers from the stream are between 0 and 100, how would you optimize it?
 */

#include <queue>
#include <functional>

using namespace std;

class MedianFinder1 {
public:
    /** initialize your data structure here. */
    MedianFinder1() {
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

/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder* obj = new MedianFinder();
 * obj->addNum(num);
 * double param_2 = obj->findMedian();
 */


class OppositeHeap {
public:
    OppositeHeap()
    {
        pq_right = priority_queue<int, vector<int>, greater<int>>();
        pq_left = priority_queue<int>();
        left_cnt = 0, right_cnt = 0;
    }

    double query()
    {
        double left = pq_left.top();
        if(left_cnt == right_cnt + 1)
            return left;
        double right = pq_right.top();
        return (left + right) / 2;
    }

    void insert(int x)
    {
        if(pq_left.empty() || x <= pq_left.top())
        {
            pq_left.push(x);
            ++left_cnt;
        }
        else
        {
            pq_right.push(x);
            ++right_cnt;
        }
        balance();
    }

private:
    priority_queue<int, vector<int>, greater<int>> pq_right;
    priority_queue<int> pq_left;
    int left_cnt, right_cnt;

    void balance()
    {
        if(left_cnt > right_cnt + 1)
        {
            pq_right.push(pq_left.top());
            pq_left.pop();
            ++right_cnt;
            --left_cnt;
        }
        else if(left_cnt < right_cnt)
        {
            pq_left.push(pq_right.top());
            pq_right.pop();
            ++left_cnt;
            --right_cnt;
        }
    }
};


class MedianFinder {
public:
    MedianFinder() {
        opposite_heap = OppositeHeap();
    }

    void addNum(int num) {
        opposite_heap.insert(num);
    }

    double findMedian() {
        return opposite_heap.query();
    }

private:
    OppositeHeap opposite_heap;
};
