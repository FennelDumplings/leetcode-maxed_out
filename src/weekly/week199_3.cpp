




#include "../include/Node.h"
#include <unordered_map>
#include <map>
#include <vector>

using namespace std;

class Solution {
public:
    int countPairs(TreeNode* root, int distance) {
        if(!root) return 0;
        int result = 0;
        _postOrder(root, distance, result);
        return result;
    }

private:
    map<int, int> _postOrder(TreeNode* node, int d, int& result)
    {
        // 返回 叶子到 node 的距离 -> 叶子数量
        if(!node -> left && !node -> right)
        {
            map<int, int> result;
            result[0] = 1;
            return result;
        }
        map<int, int> mapping_left, mapping_right;
        if(node -> left)
            mapping_left = _postOrder(node -> left, d, result);
        if(node -> right)
            mapping_right = _postOrder(node -> right, d, result);
        auto it = mapping_left.begin();
        while(it != mapping_left.end() && (it -> first < d - 1))
        {
            auto it_r = mapping_right.begin();
            while(it_r != mapping_right.end() && it_r -> first < d - it -> first - 1)
            {
                result += it -> second * it_r -> second;
                ++it_r;
            }
            ++it;
        }
        map<int, int> mapping;
        for(auto i: mapping_left)
            mapping[i.first + 1] += i.second;
        for(auto i: mapping_right)
            mapping[i.first + 1] += i.second;
        return mapping;
    }
};
