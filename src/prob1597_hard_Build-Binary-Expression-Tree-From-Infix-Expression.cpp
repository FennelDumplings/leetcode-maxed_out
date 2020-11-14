// prob1597: Build Binary Expression Tree From Infix Expression

/*
 * https://leetcode-cn.com/problems/build-binary-expression-tree-from-infix-expression/
 */

/**
 * Definition for a binary tree node.
 */

#include <stack>
#include <unordered_map>

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
    Node* expTree(string s) {
        int n = s.size();
        int i = 0;
        stack<char> st_symbol;
        stack<Node*> st_node;
        while(i < n)
        {
            if(s[i] == '(')
            {
                st_symbol.push('(');
            }
            else if(s[i] == ')')
            {
                while(!st_symbol.empty() && st_symbol.top() != '(')
                {
                    make_node(st_symbol, st_node);
                }
                st_symbol.pop();
            }
            else if(s[i] >= '0' && s[i] <= '9')
            {
                Node *node = new Node(s[i]);
                st_node.push(node);
            }
            else
            {
                while(!st_symbol.empty() && symbol_priority[st_symbol.top()] >= symbol_priority[s[i]])
                {
                    make_node(st_symbol, st_node);
                }
                st_symbol.push(s[i]);
            }
            ++i;
        }
        while(!st_symbol.empty())
        {
            make_node(st_symbol, st_node);
        }
        return st_node.top();
    }

private:
    void make_node(stack<char>& st_symbol, stack<Node*>& st_node)
    {
        char op = st_symbol.top();
        st_symbol.pop();
        Node *node = new Node(op);
        Node *right = st_node.top();
        st_node.pop();
        Node *left = st_node.top();
        st_node.pop();
        node -> left = left;
        node -> right = right;
        st_node.push(node);
    }

    unordered_map<char, int> symbol_priority = {
        {'(', 0}, {'+', 1}, {'-', 1}, {'*', 2}, {'/', 2}
    };
};
