// prob272: Closest Binary Search Tree Value II

/*
 * Given a non-empty binary search tree and a target value, find k values in the BST that are closest to the target.
 * Note:
 * Given target value is a floating point.
 * You may assume k is always valid, that is: k ≤ total nodes.
 * You are guaranteed to have only one unique set of k values in the BST that are closest to the target.
 */

/*
 * Example:
 * Input: root = [4,2,5,1,3], target = 3.714286, and k = 2
 *     4
 *    / \
 *   2   5
 *  / \
 * 1   3
 * Output: [4,3]
 */

#include "include/Node.h"
#include <deque>
#include <vector>
#include <cmath>
#include <unordered_map>

using namespace std;

// 二分查找
// 先找最接近的 *closest
// 找 closest 的过程中访问到的点都用哈希表记录它的父节点
// 然后找 closest 的 k 个前驱，和 k 个后继
// 然后合并
class Solution {
public:
    vector<int> closestKValues(TreeNode* root, double target, int k) {
        TreeNode *closest = root;
        double min_gap = abs(root -> val - target);
        unordered_map<TreeNode*, TreeNode*> father;
        father[root] = nullptr;
        _bisearch(root, target, closest, min_gap, father);
        vector<int> result(k);
        result[0] = closest -> val;
        TreeNode *precursor = _get_precursor(closest, father);
        TreeNode *successor = _get_successor(closest, father);
        for(int i = 1; i < k; ++i)
        {
            if(!successor)
            {
                result[i] = precursor -> val;
                precursor = _get_precursor(precursor, father);
                continue;
            }
            if(!precursor)
            {
                result[i] = successor -> val;
                successor = _get_successor(successor, father);
                continue;
            }
            if(abs(precursor -> val - target) < abs(successor -> val - target))
            {
                result[i] = precursor -> val;
                precursor = _get_precursor(precursor, father);
            }
            else
            {
                result[i] = successor -> val;
                successor = _get_successor(successor, father);
            }
        }
        return result;
    }

private:
    TreeNode* _get_precursor(TreeNode* node, unordered_map<TreeNode*, TreeNode*>& father)
    {
        if(node -> left)
        {
            father[node -> left] = node;
            node = node -> left;
            while(node -> right)
            {
                father[node -> right] = node;
                node = node -> right;
            }
            return node;
        }
        while(father[node] && father[node] -> right != node)
            node = father[node];
        return father[node];
    }

    TreeNode* _get_successor(TreeNode* node, unordered_map<TreeNode*, TreeNode*>& father)
    {
        if(node -> right)
        {
            father[node -> right] = node;
            node = node -> right;
            while(node -> left)
            {
                father[node -> left] = node;
                node = node -> left;
            }
            return node;
        }
        while(father[node] && father[node] -> left != node)
            node = father[node];
        return father[node];
    }

    void _bisearch(TreeNode* node, double target, TreeNode*& closest, double& min_gap,
            unordered_map<TreeNode*, TreeNode*>& father)
    {
        if(abs(node -> val - target) < min_gap)
        {
            min_gap = abs(node -> val - target);
            closest = node;
        }
        if(node -> val > target && node -> left)
        {
            father[node -> left] = node;
            _bisearch(node -> left, target, closest, min_gap, father);
        }
        if(node -> val < target && node -> right)
        {
            father[node -> right] = node;
            _bisearch(node -> right, target, closest, min_gap, father);
        }
    }
};

// 中序遍历
class Solution_2 {
public:
    vector<int> closestKValues(TreeNode* root, double target, int k) {
        deque<int> deq;
        _inOrder(root, target, k, deq);
        vector<int> result(deq.begin(), deq.end());
        return result;
    }

private:
    bool _inOrder(TreeNode* root, double target, int k, deque<int>& deq)
    {
        if(root -> left)
            if(_inOrder(root -> left, target, k, deq))
                return true;

        if((int)deq.size() < k)
        {
            deq.push_back(root -> val);
        }
        else if(max(abs(deq.back() - target), abs(deq.front() - target)) <= abs(root -> val - target))
            return true;
        else
        {
            if(abs(deq.back() - target) < abs(deq.front() - target))
                deq.pop_front();
            else
                deq.pop_back();
            deq.push_back(root -> val);
        }

        if(root -> right)
            if(_inOrder(root -> right, target, k, deq))
                return true;

        return false;
    }
};

