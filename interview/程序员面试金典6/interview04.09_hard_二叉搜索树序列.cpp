// interview04.09: 二叉搜索树序列

/*
 * https://leetcode-cn.com/problems/bst-sequences-lcci/
 */

#include <vector>
#include "../../include/Node.h"

using namespace std;

class Solution {
public:
    vector<vector<int>> BSTSequences(TreeNode* root) {
        if(!root) return {{}};
        return _postOrder(root);
    }

private:
    vector<vector<int>> _postOrder(TreeNode* node)
    {
        if(!node -> left && !node -> right)
            return {{node -> val}};

        vector<vector<int>> left, right;
        if(node -> left)
            left = _postOrder(node -> left);
        if(node -> right)
            right = _postOrder(node -> right);

        vector<vector<int>> result;
        if(left.empty())
        {
            for(const vector<int> &path: right)
            {
                result.push_back({node -> val});
                result.back().insert(result.back().end(), path.begin(), path.end());
            }
            return result;
        }
        if(right.empty())
        {
            for(const vector<int> &path: left)
            {
                result.push_back({node -> val});
                result.back().insert(result.back().end(), path.begin(), path.end());
            }
            return result;
        }
        for(const vector<int> &path_left: left)
        {
            for(const vector<int> &path_right: right)
            {
                vector<vector<int>> merged;
                vector<int> item;
                merge(path_left, path_right, 0, 0, merged, item);
                for(const vector<int> &l: merged)
                {
                    result.push_back({node -> val});
                    result.back().insert(result.back().end(), l.begin(), l.end());
                }
            }
        }
        return result;
    }

    void merge(const vector<int>& left, const vector<int>& right, int pos1, int pos2, vector<vector<int>>& merged, vector<int>& item)
    {
        int n1 = left.size(), n2 = right.size();
        if(pos1 == n1)
        {
            vector<int> tail(right.begin() + pos2, right.end());
            merged.push_back(item);
            merged.back().insert(merged.back().end(), tail.begin(), tail.end());
            return;
        }
        if(pos2 == n2)
        {
            vector<int> tail(left.begin() + pos1, left.end());
            merged.push_back(item);
            merged.back().insert(merged.back().end(), tail.begin(), tail.end());
            return;
        }
        item.push_back(left[pos1]);
        merge(left, right, pos1 + 1, pos2, merged, item);
        item.pop_back();
        item.push_back(right[pos2]);
        merge(left, right, pos1, pos2 + 1, merged, item);
        item.pop_back();
    }
};
