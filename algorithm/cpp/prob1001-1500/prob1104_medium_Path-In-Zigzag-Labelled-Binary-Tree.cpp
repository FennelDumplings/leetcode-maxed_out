// prob1104: Path In Zigzag Labelled Binary Tree

/*
 * https://leetcode-cn.com/problems/path-in-zigzag-labelled-binary-tree/
 */

#include <vector>
#include <cmath>

using namespace std;

class Solution {
public:
    vector<int> pathInZigZagTree(int label) {
        int level = log2(label);
        int start = label;
        if(level & 1)
            start = pow(2, level) + pow(2, level + 1) - 1 - start;
        vector<int> result(level + 1);
        result[level] = start;
        for(int l = level - 1; l >= 0; --l)
            result[l] = result[l + 1] / 2;
        for(int l = 1; l <= level; l += 2)
            result[l] = pow(2, l) + pow(2, l + 1) - 1 - result[l];
        return result;
    }
};
