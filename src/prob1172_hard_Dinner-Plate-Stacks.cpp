// prob1172: Dinner Plate Stacks

/*
 * You have an infinite number of stacks arranged in a row and numbered (left to right) from 0, each of the stacks has the same maximum capacity.
 * Implement the DinnerPlates class:
 * DinnerPlates(int capacity) Initializes the object with the maximum capacity of the stacks.
 * void push(int val) pushes the given positive integer val into the leftmost stack with size less than capacity.
 * int pop() returns the value at the top of the rightmost non-empty stack and removes it from that stack, and returns -1 if all stacks are empty.
 * int popAtStack(int index) returns the value at the top of the stack with the given index and removes it from that stack,
 * and returns -1 if the stack with that given index is empty.
 */

/*
 * Example:
 * Input:
 * ["DinnerPlates","push","push","push","push","push","popAtStack","push","push","popAtStack","popAtStack","pop","pop","pop","pop","pop"]
 * [[2],[1],[2],[3],[4],[5],[0],[20],[21],[0],[2],[],[],[],[],[]]
 * Output:
 * [null,null,null,null,null,null,2,null,null,20,21,5,4,3,1,-1]
 * Explanation:
 * DinnerPlates D = DinnerPlates(2);  // Initialize with capacity = 2
 * D.push(1);
 * D.push(2);
 * D.push(3);
 * D.push(4);
 * D.push(5);         // The stacks are now:  2  4
 *                                            1  3  5
 *                                            ﹈ ﹈ ﹈
 * D.popAtStack(0);   // Returns 2.  The stacks are now:     4
 *                                                        1  3  5
 *                                                        ﹈ ﹈ ﹈
 * D.push(20);        // The stacks are now: 20  4
 *                                            1  3  5
 *                                            ﹈ ﹈ ﹈
 * D.push(21);        // The stacks are now: 20  4 21
 *                                            1  3  5
 *                                            ﹈ ﹈ ﹈
 * D.popAtStack(0);   // Returns 20.  The stacks are now:     4 21
 *                                                         1  3  5
 *                                                         ﹈ ﹈ ﹈
 * D.popAtStack(2);   // Returns 21.  The stacks are now:     4
 *                                                         1  3  5
 *                                                         ﹈ ﹈ ﹈
 * D.pop()            // Returns 5.  The stacks are now:      4
 *                                                         1  3
 *                                                         ﹈ ﹈
 * D.pop()            // Returns 4.  The stacks are now:   1  3
 *                                                         ﹈ ﹈
 * D.pop()            // Returns 3.  The stacks are now:   1
 *                                                         ﹈
 * D.pop()            // Returns 1.  There are no stacks.
 * D.pop()            // Returns -1.  There are still no stacks.
 */

/*
 * Constraints:
 * 1 <= capacity <= 20000
 * 1 <= val <= 20000
 * 0 <= index <= 100000
 * At most 200000 calls will be made to push, pop, and popAtStack.
 */

#include <vector>
#include <stack>
#include <queue>

using namespace std;

// 堆
class DinnerPlates {
public:
    DinnerPlates(int capacity) {
        this -> capacity = capacity;
        vec = vector<stack<int>*>();
        stack<int> *st = new stack<int>();
        vec.push_back(st);
        pq_push = priority_queue<int, vector<int>, greater<int> >();
        pq_push.push(0);
        pq_pop = priority_queue<int>();
        pq_pop.push(-1);
    }

    void push(int val) {
        int push_id = pq_push.top();
        auto st = vec[push_id];
        if(st -> empty())
            pq_pop.push(push_id);
        st -> push(val);
        if((int)st -> size() == capacity)
            pq_push.pop();
        if(pq_push.empty())
        {
            stack<int> *st = new stack<int>();
            vec.push_back(st);
            pq_push.push((int)vec.size() - 1);
        }
    }

    int pop() {
        while(pq_pop.top() != -1 && vec[pq_pop.top()] -> empty())
            pq_pop.pop();
        int pop_id = pq_pop.top();
        if(pop_id == -1)
            return -1;
        auto st = vec[pop_id];
        int result = st -> top();
        if((int)st -> size() == capacity)
            pq_push.push(pop_id);
        st -> pop();
        if(st -> empty())
            pq_pop.pop();
        return result;
    }

    int popAtStack(int index) {
        int n = vec.size();
        if(n - 1 < index)
            return -1;
        auto st = vec[index];
        if(st -> empty())
            return -1;
        int result = st -> top();
        if((int)st -> size() == capacity)
            pq_push.push(index);
        st -> pop();
        return result;
    }

private:
    int capacity;
    vector<stack<int>*> vec;
    priority_queue<int> pq_pop;
    priority_queue<int, vector<int>, greater<int> > pq_push;
};

// 动态更新 push_id，pop_id
class DinnerPlates_3 {
public:
    DinnerPlates_3(int capacity) {
        this -> capacity = capacity;
        vec = vector<stack<int>*>();
        stack<int> *st = new stack<int>();
        vec.push_back(st);
        push_id = 0;
        pop_id = -1;
    }

    void push(int val) {
        auto st = vec[push_id];
        st -> push(val);
        if(pop_id < push_id)
            pop_id = push_id;
        int n = vec.size();
        while(push_id < n && (int)vec[push_id] -> size() == capacity)
            ++push_id;
        if(push_id == n)
        {
            stack<int> *st = new stack<int>();
            vec.push_back(st);
        }
    }

    int pop() {
        if(pop_id == -1)
            return -1;
        auto st = vec[pop_id];
        int result = st -> top();
        st -> pop();
        if(push_id > pop_id)
            push_id = pop_id;
        while(pop_id >= 0 && vec[pop_id] -> empty())
            --pop_id;
        return result;
    }

    int popAtStack(int index) {
        int n = vec.size();
        if(n - 1 < index)
            return -1;
        auto st = vec[index];
        if(st -> empty())
            return -1;
        int result = st -> top();
        st -> pop();
        if(push_id > index)
            push_id = index;
        while(pop_id >= 0 && vec[pop_id] -> empty())
            --pop_id;
        return result;
    }

private:
    int capacity;
    vector<stack<int>*> vec;
    int push_id;
    int pop_id;
};

// 基本版
// TLE
class DinnerPlates_2 {
public:
    DinnerPlates_2(int capacity) {
        this -> capacity = capacity;
        vec = vector<stack<int>*>();
    }

    void push(int val) {
        for(stack<int> *st: vec)
        {
            if((int)st -> size() < capacity)
            {
                st -> push(val);
                return;
            }
        }
        stack<int> *st = new stack<int>();
        st -> push(val);
        vec.push_back(st);
    }

    int pop() {
        int n = vec.size();
        for(int i = n - 1; i >= 0; --i)
        {
            auto st = vec[i];
            if(!(st -> empty()))
            {
                int result = st -> top();
                st -> pop();
                return result;
            }
        }
        return -1;
    }

    int popAtStack(int index) {
        int n = vec.size();
        if(n - 1 < index)
            return -1;
        auto st = vec[index];
        if(st -> empty())
            return -1;
        int result = st -> top();
        st -> pop();
        return result;
    }

private:
    int capacity;
    vector<stack<int>*> vec;
};
