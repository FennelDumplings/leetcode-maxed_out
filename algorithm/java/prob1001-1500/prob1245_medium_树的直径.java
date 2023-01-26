class Solution1 {
    private int ans;

    public int treeDiameter(int[][] edges) {
        int n = edges.length;
        ArrayList<Integer>[] g = new ArrayList[n + 1];
        for(int i = 0; i <= n; i++) {
            g[i] = new ArrayList<>();
        }
        for(int[] edge: edges) {
            g[edge[0]].add(edge[1]);
            g[edge[1]].add(edge[0]);
        }
        ans = 0;
        dfs(0, -1, g);
        return ans;
    }
    private int dfs(int u, int fa, ArrayList<Integer>[] g) {
        int max1 = 0;
        int max2 = 0;
        for(int v: g[u]) {
            if(v != fa) {
                int t = dfs(v, u, g) + 1;
                if(max1 < t) {
                    max2 = max1;
                    max1 = t;
                } else if (max2 < t){
                    max2 = t;
                }
            }
        }
        ans = Math.max(ans, (max1 + max2));
        return max1;
    }
}


class Solution {
    private int x; // 最远的点 x
    private int max_len; // 最长距离

    public int treeDiameter(int[][] edges) {
        int n = edges.length;
        ArrayList<Integer>[] g = new ArrayList[n + 1];
        for(int i = 0; i <= n; i++) {
            g[i] = new ArrayList<>();
        }
        for(int[] edge: edges) {
            g[edge[0]].add(edge[1]);
            g[edge[1]].add(edge[0]);
        }
        max_len = 0;
        x = 0;
        dfs(0, -1, 0, g);
        dfs(x, -1, 0, g);
        return max_len;
    }
    private void dfs(int u, int fa, int d, ArrayList<Integer>[] g) {
        if(d > max_len) {
            max_len = d;
            x = u;
        }
        for(int v: g[u]) {
            if(v != fa) {
                dfs(v, u, d + 1, g);
            }
        }
    }
}
