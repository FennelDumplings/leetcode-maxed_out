// prob1120: Maximum Average Subtree

/*
 * https://leetcode-cn.com/problems/maximum-average-subtree/
 */

#include "include/Node.h"
#include <vector>

using namespace std;

struct Info
{
    double sum;
    double cnt;
    Info(double s=0.0, double c=0.0):sum(s),cnt(c){}
};

class Solution {
public:
    double maximumAverageSubtree(TreeNode* root) {
        double ans = -1;
        _postOrder(root, ans);
        return ans;
    }

private:
    Info _postOrder(TreeNode* node, double& ans)
    {
        Info left(0.0, 0.0), right(0.0, 0.0);
        if(node -> left)
            left = _postOrder(node -> left, ans);
        if(node -> right)
            right = _postOrder(node -> right, ans);
        Info result(left.sum + right.sum + node -> val, left.cnt + right.cnt + 1);
        double cand = result.sum / result.cnt;
        ans = max(ans, cand);
        return result;
    }
};
