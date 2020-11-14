// prob1628: Design an Expression Tree With Evaluate Function

/*
 * https://leetcode-cn.com/problems/design-an-expression-tree-with-evaluate-function/
 */

#include <string>
#include <vector>
#include <stack>
#include <sstream>
#include <unordered_set>

using namespace std;

/**
 * This is the interface for the expression tree Node.
 * You should not remove it, and you can define some classes to implement it.
 */

class Node {
public:
    virtual ~Node () {};
    virtual int evaluate() const = 0;
};

class ETNode:public Node
{
public:
    ETNode(int num, char symbol)
    {
        this -> num = num;
        this -> symbol = symbol;
        this -> left = nullptr;
        this -> right = nullptr;
    }

    int evaluate() const
    {
        return _postOrder(this);
    }

    void set_left(ETNode* left)
    {
        this -> left = left;
    }

    void set_right(ETNode* right)
    {
        this -> right = right;
    }

private:
    ETNode *left, *right;
    int num;
    char symbol;

    int _postOrder(const ETNode* node) const
    {
        if(!node -> left && !node -> right)
        {
            return node -> num;
        }
        int ans_left =  _postOrder(node -> left);
        int ans_right =  _postOrder(node -> right);
        if(node -> symbol == '/')
            return ans_left / ans_right;
        else if(node -> symbol == '*')
            return ans_left * ans_right;
        else if(node -> symbol == '-')
            return ans_left - ans_right;
        else
            return ans_left + ans_right;
    }
};

/**
 * This is the TreeBuilder class.
 * You can treat it as the driver code that takes the postinfix input
 * and returns the expression tree represnting it as a Node.
 */

class TreeBuilder {
public:
    Node* buildTree(vector<string>& postfix) {
        stack<ETNode*> st;
        for(string s: postfix)
        {
            if(symbol.count(s[0]) > 0)
            {
                ETNode *node = new ETNode(1e9 + 1, s[0]);
                node -> set_right(st.top());
                st.pop();
                node -> set_left(st.top());
                st.pop();
                st.push(node);
            }
            else
            {
                stringstream ss;
                ss << s;
                int num;
                ss >> num;
                ETNode *node = new ETNode(num, '#');
                st.push(node);
            }
        }
        return st.top();
    }

private:
    unordered_set<char> symbol = {
        '+', '-', '*', '/'
    };
};
