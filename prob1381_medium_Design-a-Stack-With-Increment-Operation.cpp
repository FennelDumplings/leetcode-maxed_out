// prob1381: Design a Stack With Increment Operation

/*
 * Design a stack which supports the following operations.
 * Implement the CustomStack class:
 * CustomStack(int maxSize) Initializes the object with maxSize which is the maximum number of elements in the
 * stack or do nothing if the stack reached the maxSize.
 * void push(int x) Adds x to the top of the stack if the stack hasn't reached the maxSize.
 * int pop() Pops and returns the top of stack or -1 if the stack is empty.
 * void inc(int k, int val) Increments the bottom k elements of the stack by val. If there are less than k elements in the
 * stack, just increment all the elements in the stack.
 */

/*
 * Constraints:
 * 1 <= maxSize <= 1000
 * 1 <= x <= 1000
 * 1 <= k <= 1000
 * 0 <= val <= 100
 * At most 1000 calls will be made to each method of increment, push and pop each separately.
 */

#include <vector>

using namespace std;

class CustomStack {
public:
    CustomStack(int maxSize) {
        _vec = vector<int>(maxSize);
        _size = 0;
        _capacity = maxSize;
    }

    void push(int x) {
        if(_size == _capacity) return;
        _vec[_size] = x;
        ++_size;
    }

    int pop() {
        if(_size == 0) return -1;
        --_size;
        int res = _vec[_size];
        return res;
    }

    void increment(int k, int val) {
        int kk = min(k, _size);
        // 0 ~ kk -1
        for(int i = 0; i < kk; ++i)
            _vec[i] += val;
    }

private:
    vector<int> _vec;
    int _size;
    int _capacity;
};

/**
 * Your CustomStack object will be instantiated and called as such:
 * CustomStack* obj = new CustomStack(maxSize);
 * obj->push(x);
 * int param_2 = obj->pop();
 * obj->increment(k,val);
 */
