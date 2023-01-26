// prob1388: Pizza With 3n Slices

/*
 * There is a pizza with 3n slices of varying size, you and your friends will take slices of pizza as follows:
 * You will pick any pizza slice.
 * Your friend Alice will pick next slice in anti clockwise direction of your pick. 
 * Your friend Bob will pick next slice in clockwise direction of your pick.
 * Repeat until there are no more slices of pizzas.
 * Sizes of Pizza slices is represented by circular array slices in clockwise direction.
 * Return the maximum possible sum of slice sizes which you can have.
 */

/*
 * Example 1:
 * Input: slices = [1,2,3,4,5,6]
 * Output: 10
 * Explanation: Pick pizza slice of size 4, Alice and Bob will pick slices with size 3 and 5 respectively. Then Pick slices with size 6, finally Alice and Bob will pick slice of size 2 and 1 respectively. Total = 4 + 6.
 * Example 2:
 * Input: slices = [8,9,8,6,1,1]
 * Output: 16
 * Output: Pick pizza slice of size 8 in each turn. If you pick slice with size 9 your partners will pick slices of size 8.
 * Example 3:
 * Input: slices = [4,1,2,5,8,3,1,9,7]
 * Output: 21
 * Example 4:
 * Input: slices = [3,1,2]
 * Output: 3
 */

/*
 * Constraints:
 * 1 <= slices.length <= 500
 * slices.length % 3 == 0
 * 1 <= slices[i] <= 1000
 */

// DP

#include <vector>
#include <list>
#include <algorithm>
#include <iterator>
#include <queue>

using namespace std;

class Solution {
public:
    // dp[i][j] := 考虑到 i, 取 j 个的答案
    int maxSizeSlices(vector<int>& slices) {
        int n = slices.size();
        vector<vector<int> > dp(n, vector<int>(n / 3 + 1, -1));
        vector<int> vec(slices.begin(), slices.end() - 1);
        int result1 = _solve(vec, n - 1, n / 3, dp);
        dp.assign(n + 1, vector<int>(n / 3 + 1, -1));
        vec.assign(slices.begin() + 1, slices.end());
        int result2 = _solve(vec, n - 1, n / 3, dp);
        return max(result1, result2);
    }

private:
    int _solve(const vector<int>& slices, int i, int j, vector<vector<int> >& dp)
    {
        if(dp[i][j] != -1) return dp[i][j];

        if(i == 0 || j == 0) return dp[i][j] = 0;
        if(i == 1 && j == 1) return dp[i][j] = slices[i - 1];

        dp[i][j] = _solve(slices, i - 1, j, dp);
        if(i >= 2)
            dp[i][j] = max(dp[i][j], _solve(slices, i - 2, j - 1, dp) + slices[i - 1]);

        return dp[i][j];
    }
};


// 贪心 + 双链表模拟
struct DoubleListNode {
    int val;
    DoubleListNode *next;
    DoubleListNode *prev;
    DoubleListNode(int x) : val(x), next(nullptr), prev(nullptr) {}
};

class DoubleCircleList {
public:
    /** Initialize your data structure here. Set the size of the deque to be k. */
    DoubleCircleList() {
        head = new DoubleListNode(0);
        head -> next = head;
        head -> prev = head;
        tail = head;
        length = 0;
    }

    DoubleListNode* insert(DoubleListNode *pos, int val)
    {
        DoubleListNode *cur = new DoubleListNode(val);
        cur -> next = pos -> next;
        cur -> prev = pos;
        pos -> next -> prev = cur;
        pos -> next = cur;
        if(tail == pos)
            tail = cur;
        ++length;
        return cur;
    }

    /** Adds an item at the rear of Deque. Return true if the operation is successful. */
    bool insertLast(int value) {
        DoubleListNode *cur = new DoubleListNode(value);
        cur -> next = head;
        cur -> prev = tail;
        tail -> next = cur;
        head -> prev = cur;
        tail = cur;
        ++length;
        return true;
    }

    DoubleListNode* delete_(DoubleListNode *pos)
    {
        pos -> prev -> next = pos -> next;
        pos -> next -> prev = pos -> prev;
        DoubleListNode *result = pos -> prev;
        pos = nullptr;
        if(head -> next == head)
            tail = head;
        return result;
    }

    void change(DoubleListNode* pos, int val)
    {
        pos -> val = val;
    }

    bool is_head(DoubleListNode *pos)
    {
        return pos == head;
    }

    DoubleListNode* get_next(DoubleListNode *pos)
    {
        return pos -> next;
    }

    DoubleListNode* get_prev(DoubleListNode *pos)
    {
        return pos -> prev;
    }

    DoubleListNode* get_head()
    {
        return head;
    }

    void traverse()
    {
        auto iter = head -> next;
        while(iter != head)
        {
            cout << iter -> val << " ";
            iter = iter -> next;
        }
        cout << endl;
    }

private:
    DoubleListNode *head, *tail;
    int length;
};

class Solution {
public:
    int maxSizeSlices(vector<int>& slices) {
        int n = slices.size();
        DoubleCircleList dclist;
        for(int i: slices) dclist.insertLast(i);
        priority_queue<PID, vector<PID>, Cmp> pq;
        DoubleListNode *it = dclist.get_head();
        vector<DoubleListNode*> deletelist;
        for(int i = 0; i < n; ++i)
        {
            it = dclist.get_next(it);
            pq.push(PID(it -> val, it));
        }
        int result = 0;
        for(int i = 0; i < n / 3; ++i)
        {
            while(pq.top().second -> next -> prev != pq.top().second)
            {
                deletelist.push_back(pq.top().second);
                pq.pop();
            }
            DoubleListNode *cur = pq.top().second;
            pq.pop();
            result += cur -> val;
            int new_val = 0 - cur -> val;
            DoubleListNode *it_left = dclist.get_prev(cur), *it_right = dclist.get_next(cur);
            if(dclist.is_head(it_left)) it_left = dclist.get_prev(it_left);
            if(dclist.is_head(it_right)) it_right = dclist.get_next(it_right);
            new_val += it_left -> val + it_right -> val;
            dclist.delete_(it_left);
            dclist.delete_(it_right);
            dclist.change(cur, new_val);
            //dclist.traverse();
            pq.push(PID(new_val, cur));
        }
        for(DoubleListNode *node: deletelist)
            delete node;
        return result;
    }

private:
    using PID = pair<int, DoubleListNode*>;

    struct Cmp
    {
        bool operator()(const PID& a1, const PID& a2) const
        {
            return a1.first < a2.first;
        }
    };
};
