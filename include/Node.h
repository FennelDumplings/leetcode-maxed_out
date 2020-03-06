#ifndef NODE_H_INCLUDED
#define NODE_H_INCLUDED

//Definition for singly-linked list
//struct ListNode;
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};


//Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 };


 //Definition for an interval.
struct Interval {
    int start;
    int end;
    Interval() : start(0), end(0) {}
    Interval(int s, int e) : start(s), end(e) {}
};

// 线段树节点
struct STNode {
    int start;
    int end;
    int sum;
    STNode *left;
    STNode *right;
    STNode(){}
    STNode(int start, int end, int sum)
        :start(start),end(end),sum(sum),left(nullptr),right(nullptr){}
    STNode(int start, int end, int sum, STNode *left, STNode *right)
        :start(start),end(end),sum(sum),left(left),right(right){}
};

#endif // NODE_H_INCLUDED
