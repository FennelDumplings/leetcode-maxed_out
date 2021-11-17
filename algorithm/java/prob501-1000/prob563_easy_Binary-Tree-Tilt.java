import java.lang.Math;

class Solution {
    int ans = 0;

    public int findTilt(TreeNode root) {
        if(root == null)
            return 0;
        dfs(root);
        return ans;
    }

    public int dfs(TreeNode node) {
        int left_sum = 0;
        int right_sum = 0;
        if(node.left != null) {
            left_sum = dfs(node.left);
        }
        if(node.right != null) {
            right_sum = dfs(node.right);
        }
        ans += Math.abs(left_sum - right_sum);
        return left_sum + right_sum + node.val;
    }
}
