// interview03.01: Three in One LCCI

/*
 * Describe how you could use a single array to implement three stacks.
 * Yout should implement push(stackNum, value)、pop(stackNum)、isEmpty(stackNum)、peek(stackNum) methods. 
 * stackNum is the index of the stack. value is the value that pushed to the stack.
 * The constructor requires a stackSize parameter, which represents the size of each stack.
 */

/*
 * Example1:
 *  Input:
 * ["TripleInOne", "push", "push", "pop", "pop", "pop", "isEmpty"]
 * [[1], [0, 1], [0, 2], [0], [0], [0], [0]]
 *  Output:
 * [null, null, null, 1, -1, -1, true]
 * Explanation: When the stack is empty, `pop, peek` return -1. When the stack is full, `push` does nothing.
 * Example2:
 *  Input:
 * ["TripleInOne", "push", "push", "push", "pop", "pop", "pop", "peek"]
 * [[2], [0, 1], [0, 2], [0, 3], [0], [0], [0], [0]]
 *  Output:
 * [null, null, null, null, 2, 1, -1, -1]
 */

/**
 * Your TripleInOne object will be instantiated and called as such:
 * TripleInOne* obj = new TripleInOne(stackSize);
 * obj->push(stackNum,value);
 * int param_2 = obj->pop(stackNum);
 * int param_3 = obj->peek(stackNum);
 * bool param_4 = obj->isEmpty(stackNum);
 */

#include <vector>

using namespace std;

class TripleInOne {
public:
    TripleInOne(int stackSize) {
        vec = vector<int>(1 + 3 * stackSize, 0);
        for(int i = 0; i <= 2; ++i)
        {
            stack_top[i] = i * stackSize;
            stack_lower_bound[i] = i * stackSize;
            stack_upper_bound[i] = (i + 1) * stackSize;
        }
    }

    void push(int stackNum, int value) {
        if(isFull(stackNum))
            return;
        vec[++stack_top[stackNum]] = value;
    }

    int pop(int stackNum) {
        if(isEmpty(stackNum))
            return -1;
        return vec[stack_top[stackNum]--];
    }

    int peek(int stackNum) {
        if(isEmpty(stackNum))
            return -1;
        return vec[stack_top[stackNum]];
    }

    bool isEmpty(int stackNum) {
        return stack_top[stackNum] == stack_lower_bound[stackNum];
    }

    bool isFull(int stackNum)
    {
        return stack_top[stackNum] == stack_upper_bound[stackNum];
    }

private:
    vector<int> vec;
    int stack_top[3];
    int stack_upper_bound[3];
    int stack_lower_bound[3];
};
