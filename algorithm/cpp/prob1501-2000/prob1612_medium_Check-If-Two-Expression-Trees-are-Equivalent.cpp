// prob1612: Check If Two Expression Trees are Equivalent

/*
 * https://leetcode-cn.com/problems/check-if-two-expression-trees-are-equivalent/
 */

/**
 * Definition for a binary tree node.
 */

#include <vector>

using namespace std;

struct Node {
    char val;
    Node *left;
    Node *right;
    Node() : val(' '), left(nullptr), right(nullptr) {}
    Node(char x) : val(x), left(nullptr), right(nullptr) {}
    Node(char x, Node *left, Node *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    bool checkEquivalence(Node* root1, Node* root2) {
        return evaluate(root1) == evaluate(root2);
    }

private:
    vector<int> evaluate(Node* node)
    {
        vector<int> res(26);
        if(node -> val == '+' || node -> val == '-')
        {
            vector<int> left = evaluate(node -> left);
            vector<int> right = evaluate(node -> right);
            if(node -> val == '+')
            {
                for(int i = 0; i < 26; ++i)
                    res[i] = left[i] + right[i];
            }
            else
            {
                for(int i = 0; i < 26; ++i)
                    res[i] = left[i] - right[i];
            }
        }
        else
            ++res[node -> val - 'a'];
        return res;
    }
};
