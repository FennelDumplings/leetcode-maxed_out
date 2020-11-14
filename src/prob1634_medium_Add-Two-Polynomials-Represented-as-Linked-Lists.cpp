// prob1634: Add Two Polynomials Represented as Linked Lists

/*
 * https://leetcode-cn.com/problems/add-two-polynomials-represented-as-linked-lists/
 */

/**
 * Definition for polynomial singly-linked list.
 */

struct PolyNode {
    int coefficient, power;
    PolyNode *next;
    PolyNode(): coefficient(0), power(0), next(nullptr) {};
    PolyNode(int x, int y): coefficient(x), power(y), next(nullptr) {};
    PolyNode(int x, int y, PolyNode* next): coefficient(x), power(y), next(next) {};
};

class Solution {
public:
    PolyNode* addPoly(PolyNode* poly1, PolyNode* poly2) {
        if(!poly2) return poly1;
        if(!poly1) return poly2;
        PolyNode *dummy = new PolyNode(0, 0);
        PolyNode *iter = dummy;
        PolyNode *it1 = poly1, *it2 = poly2;
        while(it1 && it2)
        {
            if(it1 -> power == it2 -> power)
            {
                int p = it1 -> power;
                int c = it1 -> coefficient + it2 -> coefficient;
                if(c != 0)
                    iter -> next = new PolyNode(c, p);
                it1 = it1 -> next;
                it2 = it2 -> next;
            }
            else if(it1 -> power > it2 -> power)
            {
                iter -> next = new PolyNode(it1 -> coefficient, it1 -> power);
                it1 = it1 -> next;
            }
            else
            {
                iter -> next = new PolyNode(it2 -> coefficient, it2 -> power);
                it2 = it2 -> next;
            }
            if(iter -> next)
                iter = iter -> next;
        }
        while(it1)
        {
            iter -> next = new PolyNode(it1 -> coefficient, it1 -> power);
            it1 = it1 -> next;
            iter = iter -> next;
        }
        while(it2)
        {
            iter -> next = new PolyNode(it2 -> coefficient, it2 -> power);
            it2 = it2 -> next;
            iter = iter -> next;
        }
        return dummy -> next;
    }
};
