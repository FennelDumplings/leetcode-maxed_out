// prob346: Moving Average from Data Stream

/*
 * Given a stream of integers and a window size, calculate the moving average of all integers in the sliding window.
 */

/*
 * Example:
 *
 * MovingAverage m = new MovingAverage(3);
 * m.next(1) = 1
 * m.next(10) = (1 + 10) / 2
 * m.next(3) = (1 + 10 + 3) / 3
 * m.next(5) = (10 + 3 + 5) / 3
 */

#include <vector>

using namespace std;

class MovingAverage {
public:
    /** Initialize your data structure here. */
    MovingAverage(int size) {
        sum = 0;
        window_len = size;
        nums = vector<int>();
        len = 0;
    }

    double next(int val) {
        nums.push_back(val);
        ++len;
        sum += val;
        if(len <= window_len)
            return (double)sum / len;
        sum -= nums[len - window_len - 1];
        return (double)sum / window_len;
    }

private:
    int sum;
    vector<int> nums;
    int window_len;
    int len;
};
