// interview09: 用两个栈实现队列

/*
 * 用两个栈实现一个队列。队列的声明如下，请实现它的两个函数 appendTail 和 deleteHead ，分别完成在队列尾部插入整数和在队列头部删除整数的功能。(若队列中没有元素，deleteHead 操作返回 -1 )
 */

#include <stack>

using namespace std;

class CQueue {
public:
    CQueue() {
        st_in = stack<int>();
        st_out = stack<int>();
    }

    void appendTail(int value) {
        st_in.push(value);
    }

    int deleteHead() {
        if(st_out.empty())
        {
            while(!st_in.empty())
            {
                st_out.push(st_in.top());
                st_in.pop();
            }
        }
        if(st_out.empty())
            return -1;
        int result = st_out.top();
        st_out.pop();
        return result;
    }

private:
    stack<int> st_in, st_out;
};
