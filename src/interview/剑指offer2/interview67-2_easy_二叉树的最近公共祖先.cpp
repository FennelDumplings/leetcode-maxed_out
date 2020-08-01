// interview67-2: 二叉树的最近公共祖先

/*
 * https://leetcode-cn.com/problems/er-cha-shu-de-zui-jin-gong-gong-zu-xian-lcof/
 */

#include "../../include/Node.h"
#include <list>
#include <iterator>

using namespace std;

class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        bool flagp = false;
        bool flagq = false;
        list<TreeNode*> listp({root}), listq({root});
        _preOrder(root, p, q, listp, listq, flagp, flagq);
        int lp = listp.size();
        int lq = listq.size();
        list<TreeNode*>::iterator itp = listp.begin();
        list<TreeNode*>::iterator itq = listq.begin();
        if(lp - lq > 0)
            advance(itp, lp - lq);
        if(lq - lp > 0)
            advance(itq, lq - lp);
        for(int i = 1; i <= min(lp, lq); ++i)
        {
            if(*itp == *itq)
                return *itp;
            ++itp;
            ++itq;
        }
        return nullptr;
    }

private:
    void _preOrder(TreeNode* node, TreeNode* p, TreeNode* q, list<TreeNode*>& listp, list<TreeNode*>& listq, bool& flagp, bool& flagq)
    {
        if(flagp && flagq) return;
        if(node -> left)
        {
            if(!flagp)
            {
                listp.push_front(node -> left);
                if(node -> left == p)
                    flagp = true;
            }
            if(!flagq)
            {
                listq.push_front(node -> left);
                if(node -> left == q)
                    flagq = true;
            }
            _preOrder(node -> left, p, q, listp, listq, flagp, flagq);
            if(!flagp)
                listp.pop_front();
            if(!flagq)
                listq.pop_front();
        }
        if(node -> right)
        {
            if(!flagp)
            {
                listp.push_front(node -> right);
                if(node -> right == p)
                    flagp = true;
            }
            if(!flagq)
            {
                listq.push_front(node -> right);
                if(node -> right == q)
                    flagq = true;
            }
            _preOrder(node -> right, p, q, listp, listq, flagp, flagq);
            if(!flagp)
                listp.pop_front();
            if(!flagq)
                listq.pop_front();
        }
    }
};
