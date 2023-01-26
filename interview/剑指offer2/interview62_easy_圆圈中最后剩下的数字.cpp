// 面62: 圆圈中最后剩下的数字

/*
 * 0,1,,n-1这n个数字排成一个圆圈，从数字0开始，每次从这个圆圈里删除第m个数字。求出这个圆圈里剩下的最后一个数字。
 * 例如，0、1、2、3、4这5个数字组成一个圆圈，从数字0开始每次删除第3个数字，则删除的前4个数字依次是2、0、4、1，因此最后剩下的数字是3。
 */

/*
 * 示例 1：
 * 输入: n = 5, m = 3
 * 输出: 3
 * 示例 2：
 */

/*
 * 限制：
 * 1 <= n <= 10^5
 * 1 <= m <= 10^6
 */

#include <iostream>

using namespace std;

// 递推法
class Solution_4 {
public:
    int lastRemaining(int n, int m) {
        int idx = 0; // 对应 i = 1
        for(int i = 2; i <= n; ++i)
        {
            idx = (idx + m) % i;
        }
        return idx;
    }
};

// 递推法优化
class Solution_3 {
public:
    int lastRemaining(int n, int m) {
        if (m == 1) return n - 1;
        int last = 0, t = 1;
        for (int i = 2; i <= n; i += t) {
            t = (i - last + m - 3) / (m - 1);
            if (i + t - 1 > n) {
                last += (n - i + 1) * m;
                break;
            }
            (last += t * m) %= (i + t - 1);
        }
        return last;
    }
};

// 数学法
// Ref 具体数学 -- 整数取阶
class Solution_2 {
public:
    int lastRemaining(int n, int m) {
        long D = 1, end = (long)n * (m - 1);
        while (D <= end) {
            D = (m * D + m - 2) / (m - 1);
        }
        return (long)n * m - D;
    }
};


// ------------------------

typedef int DLType;
const DLType DLTypeNULL = -1;
const int MAX_LEN = 1e6;

struct DLNode
{
    DLType val;
    DLNode *next;
    DLNode *prev;
    DLNode(DLType x) : val(x), next(nullptr), prev(nullptr) {}
};

class DoubleCircleList
{
private:
    // head 一直指向 dummy
    // tail 在空表时指向 dummy，否则指向 head 的前一个节点
    DLNode *head, *tail;
    int length;
    int capacity;

public:
    DoubleCircleList(int N=MAX_LEN)
    {
        head = new DLNode(0);
        head -> next = head;
        head -> prev = head;
        tail = head;
        length = 0;
        capacity = N;
    }

    bool removeHead()
    {
        if(isEmpty())
            return false;
        remove(get_head());
        return true;
    }

    bool removeTail()
    {
        if(isEmpty())
            return false;
        remove(get_tail());
        return true;
    }

    DLType getHead() const
    {
        if(isEmpty())
            return DLTypeNULL;
        return get_head() -> val;
    }

    DLType getTail() const
    {
        if(isEmpty())
            return DLTypeNULL;
        return get_tail() -> val;
    }

    bool insertHead(DLType val)
    {
        if(isFull())
            return false;
        insert(head, val);
        return true;
    }

    bool insertTail(DLType val)
    {
        if(isFull())
            return false;
        insert(tail, val);
        return true;
    }

    DLNode* insert(DLNode *pos, DLType val)
    {
        if(isFull())
            return nullptr;
        DLNode *cur = new DLNode(val);
        cur -> next = pos -> next;
        cur -> prev = pos;
        pos -> next -> prev = cur;
        pos -> next = cur;
        if(tail == pos)
            tail = cur;
        ++length;
        return cur;
    }

    DLType get(DLNode *pos) const
    {
        if(is_dummy(pos))
            return DLTypeNULL;
        return pos -> val;
    }

    DLNode* remove(DLNode *pos)
    {
        if(isEmpty())
            return nullptr;
        if(is_dummy(pos))
            return nullptr;
        if(tail == pos)
            tail = tail -> prev;
        --length;
        pos -> prev -> next = pos -> next;
        pos -> next -> prev = pos -> prev;
        DLNode *result = pos -> next;
        delete pos;
        pos = nullptr;
        if(isEmpty())
            return nullptr;
        if(is_dummy(result))
            result = result -> next;
        return result;
    }

    bool change(DLNode* pos, DLType val)
    {
        if(is_dummy(pos))
            return false;
        pos -> val = val;
        return true;
    }

    DLNode* get_next(DLNode *pos) const
    {
        if(isEmpty())
            return nullptr;
        if(is_tail(pos))
            return get_head();
        return pos -> next;
    }

    DLNode* get_prev(DLNode *pos) const
    {
        if(isEmpty())
            return nullptr;
        if(is_head(pos))
            return get_tail();
        return pos -> prev;
    }

    bool is_dummy(DLNode *pos) const
    {
        return pos == head;
    }

    bool is_head(DLNode *pos) const
    {
        return (!isEmpty() && pos == head -> next);
    }

    bool is_tail(DLNode *pos) const
    {
        return (!isEmpty() && pos == tail);
    }

    DLNode* get_tail() const
    {
        if(isEmpty())
            return nullptr;
        return tail;
    }

    DLNode* get_head() const
    {
        if(isEmpty())
            return nullptr;
        return head -> next;
    }


    bool isEmpty() const
    {
        return head == tail;
    }

    int size() const
    {
        return length;
    }

    bool isFull() const
    {
        return length >= capacity;
    }

    void traverse() const
    {
        auto iter = head -> next;
        while(iter != head)
        {
            cout << iter -> val << " ";
            iter = iter -> next;
        }
        cout << endl;
    }
};

class Solution {
public:
    int lastRemaining(int n, int m) {
        DoubleCircleList *dclist = new DoubleCircleList();
        for(int i = 0; i < n; ++i)
        {
            dclist -> insertTail(i);
        }
        DLNode *iter = dclist -> get_head();
        while(dclist -> size() > 1)
        {
            for(int i = 0; i < m - 1; ++i)
                iter = dclist -> get_next(iter);
            iter = dclist -> remove(iter);
        }
        return dclist -> getHead();
    }
};
