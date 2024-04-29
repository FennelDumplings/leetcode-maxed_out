

void dfs(int u, int prev, const vector<vector<vector<int>>>& g, vector<int>& d, vector<int>& parent, vector<vector<int>>& pre)
{
    // 访问从 u 出发的所有边
    for(const vector<int>& e: g[u])
    {
        int v = e[0];
        int w = e[1];
        if(v == prev)
            continue;
        d[v] = d[u] + 1;
        parent[v] = u;
        for(int x = 1; x <= 26; ++x)
            pre[x][v] = pre[x][u];
        pre[w][v]++;
        dfs(v, u, g, d, parent, pre);
    }
}

void get_fa(int N, int K, vector<vector<int>>& fa, const vector<int>& parent)
{
    // fa[i][j] := 从 i 爬 2 ^ j 步所到点的 id
    // fa[i][0] := 从 i 爬 1 步所到点的 id
    for(int i = 0; i < N; ++i)
        fa[i][0] = parent[i];
    for(int j = 1; j < K; ++j)
        fa[0][j] = -1;
    for(int j = 1; j < K; ++j)
        for(int i = 1; i < N; ++i)
        {
            if(fa[i][j - 1] == -1)
                fa[i][j] = -1;
            else
                fa[i][j] = fa[fa[i][j - 1]][j - 1];
        }
}

int lowbit(int n)
{
    return n & (-n);
}

int highbit(int n)
{
    int p = lowbit(n);
    while(p != n)
    {
        n -= p;
        p = lowbit(n);
    }
    return p;
}

int lca(int x, int y, const vector<int>& d, const vector<vector<int>>& fa)
{
    // d[x] >= d[y]
    if(d[x] < d[y])
        return lca(y, x, d, fa);
    // 将 y 向上调整直到和 x 一个深度
    int delta = d[x] - d[y];
    while(delta > 0)
    {
        x = fa[x][log2(highbit(delta))];
        delta -= highbit(delta);
    }
    if(x == y)
        return x;
    int n = d.size();
    int m = log2(n);
    while(true)
    {
        if(fa[x][0] == fa[y][0])
            break;
        int k = 1;
        while(k <= m)
        {
            if(fa[x][k] == -1 || fa[y][k] == -1)
                break;
            if(fa[x][k] == fa[y][k])
                break;
            ++k;
        }
        x = fa[x][k - 1];
        y = fa[y][k - 1];
    }
    return fa[x][0];
}

class Solution {
public:
    vector<int> minOperationsQueries(int n, vector<vector<int>>& edges, vector<vector<int>>& queries) {
        vector<vector<vector<int>>> g(n);
        for(vector<int>& e: edges)
        {
            int u = e[0];
            int v = e[1];
            int w = e[2];
            g[u].push_back({v, w});
            g[v].push_back({u, w});
        }

        vector<int> d(n, 0);
        vector<int> parent(n, -1);
        vector<vector<int>> pre(27, vector<int>(n));
        dfs(0, -1, g, d, parent, pre);

        int K = log2(n) + 1;
        vector<vector<int>> fa(n, vector<int>(K));
        get_fa(n, K, fa, parent);



        int m = queries.size();
        vector<int> result(m, -1);
        for(int i = 0; i < m; ++i)
        {
            int u = queries[i][0];
            int v = queries[i][1];
            int r = lca(u, v, d, fa);
            // cout << u << " " << v << ": " << r << endl;
            int mode = -1;
            int cnt = -1;
            for(int x = 1; x <= 26; ++x)
            {
                int tmp = pre[x][u] - pre[x][r];
                tmp += pre[x][v] - pre[x][r];
                if(tmp > cnt)
                {
                    cnt = tmp;
                    mode = x;
                }
            }
            // cout << "mode: " << mode << ", cnt: " << cnt << endl;
            int l = (d[u] - d[r]) + (d[v] - d[r]);
            // cout << l << endl;
            result[i] = l - cnt;
        }
        return result;
    }
};
