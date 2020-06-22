// prob558: Logical OR of Two Binary Grids Represented as Quad-Trees

/*
 * https://leetcode-cn.com/problems/logical-or-of-two-binary-grids-represented-as-quad-trees/
 */

/*
 * Constraints:
 * quadTree1 and quadTree2 are both valid Quad-Trees each representing a n * n grid.
 * n == 2^x where 0 <= x <= 9.
 */

#include <vector>

using namespace std;

// Definition for a QuadTree node.
class Node {
public:
    bool val;
    bool isLeaf;
    Node* topLeft;
    Node* topRight;
    Node* bottomLeft;
    Node* bottomRight;

    Node() {
        val = false;
        isLeaf = false;
        topLeft = nullptr;
        topRight = nullptr;
        bottomLeft = nullptr;
        bottomRight = nullptr;
    }

    Node(bool _val, bool _isLeaf) {
        val = _val;
        isLeaf = _isLeaf;
        topLeft = nullptr;
        topRight = nullptr;
        bottomLeft = nullptr;
        bottomRight = nullptr;
    }

    Node(bool _val, bool _isLeaf, Node* _topLeft, Node* _topRight, Node* _bottomLeft, Node* _bottomRight) {
        val = _val;
        isLeaf = _isLeaf;
        topLeft = _topLeft;
        topRight = _topRight;
        bottomLeft = _bottomLeft;
        bottomRight = _bottomRight;
    }

    ~Node()
    {
        for(Node *son: vector<Node*>{topLeft, topRight, bottomLeft, bottomRight})
        {
            if(son)
            {
                delete son;
                son = nullptr;
            }
        }
    }
};


class Solution {
public:
    Node* intersect(Node* quadTree1, Node* quadTree2) {
        if(!quadTree1) return nullptr;
        return build(quadTree1, quadTree2);
    }

private:
    Node* build(Node* root1, Node* root2)
    {
        Node *root;
        if(root1 -> isLeaf && root2 -> isLeaf)
        {
            root = new Node(root1 -> val || root2 -> val, true);
        }
        else if(!root1 -> isLeaf && !root2 -> isLeaf)
        {
            root = new Node();
            root -> topLeft = build(root1 -> topLeft, root2 -> topLeft);
            root -> topRight = build(root1 -> topRight, root2 -> topRight);
            root -> bottomLeft = build(root1 -> bottomLeft, root2 -> bottomLeft);
            root -> bottomRight = build(root1 -> bottomRight, root2 -> bottomRight);
            if(root -> topLeft -> isLeaf && root -> topRight -> isLeaf && root -> bottomLeft -> isLeaf && root -> bottomRight -> isLeaf)
            {
                bool tmp = root -> topLeft -> val;
                if(root -> topRight -> val == tmp && root -> bottomLeft -> val == tmp && root -> bottomRight -> val == tmp)
                {
                    root -> isLeaf = true;
                    root -> val = tmp;
                    root -> topLeft = nullptr;
                    root -> topRight = nullptr;
                    root -> bottomLeft = nullptr;
                    root -> bottomRight = nullptr;
                }
            }
        }
        else if(root1 -> isLeaf)
        {
            if(root1 -> val)
            {
                root = new Node(true, true);
            }
            else
            {
                root = new Node(root2 -> val, false);
                root -> topLeft = build1(root2 -> topLeft);
                root -> topRight = build1(root2 -> topRight);
                root -> bottomLeft = build1(root2 -> bottomLeft);
                root -> bottomRight = build1(root2 -> bottomRight);
            }
        }
        else
        {
            if(root2 -> val)
            {
                root = new Node(true, true);
            }
            else
            {
                root = new Node(root1 -> val, false);
                root -> topLeft = build1(root1 -> topLeft);
                root -> topRight = build1(root1 -> topRight);
                root -> bottomLeft = build1(root1 -> bottomLeft);
                root -> bottomRight = build1(root1 -> bottomRight);
            }
        }
        return root;
    }

    Node* build1(Node* root1)
    {
        Node *root = new Node(root1 -> val, root1 -> isLeaf);
        if(!root1 -> isLeaf)
        {
            root -> topLeft = build1(root1 -> topLeft);
            root -> topRight = build1(root1 -> topRight);
            root -> bottomLeft = build1(root1 -> bottomLeft);
            root -> bottomRight = build1(root1 -> bottomRight);
        }
        return root;
    }
};
