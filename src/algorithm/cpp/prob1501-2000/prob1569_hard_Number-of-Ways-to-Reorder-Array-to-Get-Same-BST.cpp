// prob1569: Number of Ways to Reorder Array to Get Same BST

/*
 * https://leetcode-cn.com/problems/number-of-ways-to-reorder-array-to-get-same-bst/
 */

#include <vector>

using namespace std;

using ll = long long;

class C
{
public:
    C(){}
    C(ll n, ll p)
    {
        preprocess(n, p);
    }

    ll operator()(ll n, ll m, ll p) const
    {
        // 先求 $n! \mod p$
        ll ans1 = jc[n];
        // 再求 $m!(n-m)! \mod p$ 的逆元
        ll ans2 = (jc_inv[m] * jc_inv[n - m]) % p;
        // 再乘起来
        return (ans1 * ans2) % p;
    }

private:
    vector<ll> jc, jc_inv;

    void preprocess(ll n, ll p)
    {
        // jc[i] = i! % p
        jc = vector<ll>(n + 1, 1);
        for(ll i = 1; i <= n; ++i)
            jc[i] = (jc[i - 1] * i) % p;
        jc_inv = vector<ll>(n + 1, 1);
        // 0 不存在逆元
        for(ll i = 1; i <= n; ++i)
            jc_inv[i] = inv(jc[i], p);
    }

    // 扩展欧几里得求 ax + by = gcd(a, b)
    ll exgcd(ll a, ll b, ll& x, ll& y)
    {
        // 求出 ax + by = gcd(a, b) 的一组特接并返回 a,b 的最大公约数 d。
        if(b == 0)
        {
            x = 1;
            y = 0;
            return a;
        }
        ll d = exgcd(b, a % b, x, y);
        int z = x;
        x = y;
        y = z - y * (a / b);
        return d;
    }

    // 求 b 模 p 的乘法逆元 (b 与 p 互质)
    ll inv(ll b, ll p)
    {
        // 解方程 bx 与 1 模 p 同余
        // 扩展欧几里得求 bx0 + py0 = 1
        ll x0 = 0, y0 = 0;
        ll d = exgcd(b, p, x0, y0);
        if(d != 1) // b 和 p 不互质的情况不不存在逆元
            return -1;
        return (x0 % p + p) % p;
    }
};

struct Node
{
    int id;
    int left, right;
    int size;
    Node(int id, int left = 0, int right = 0, int size = 1):id(id),left(left),right(right),size(size){}
};

class Solution {
public:
    int numOfWays(vector<int>& nums) {
        int n = nums.size();
        vector<Node> tree(n + 1, Node(0));
        for(int i = 1; i <= n; ++i)
            tree[i].id = i;
        comb = C(n, MOD);
        int root = nums[0];
        for(int i = 0; i < n; ++i)
        {
            int node = nums[i];
            insert(tree, root, node);
        }
        int ans = dfs(tree, root);
        ans = (ans - 1 + MOD) % MOD;
        return ans;
    }

private:
    const int MOD = 1e9 + 7;
    C comb;

    int dfs(const vector<Node>& tree, int node)
    {
        if(is_leaf(tree, node))
            return 1;
        int left_size = tree[node].left == 0 ? 0 : tree[tree[node].left].size;
        int c = comb(tree[node].size - 1, left_size, MOD); // C(n, m) 返回 C(n, m)%p
        int ans = c;
        if(tree[node].left != 0)
        {
            int left_cnt = dfs(tree, tree[node].left);
            ans = ((ll)ans * left_cnt) % MOD;
        }
        if(tree[node].right != 0)
        {
            int right_cnt = dfs(tree, tree[node].right);
            ans = ((ll)ans * right_cnt) % MOD;
        }
        return ans;
    }

    bool is_leaf(const vector<Node>& tree, int node)
    {
        return tree[node].left == 0 && tree[node].right == 0;
    }

    void insert(vector<Node>& tree, int root, int node)
    {
        if(node == root)
            return;
        ++tree[root].size;
        if(node < root)
        {
            if(tree[root].left == 0)
            {
                tree[root].left = node;
                return;
            }
            insert(tree, tree[root].left, node);
        }
        if(node > root)
        {
            if(tree[root].right == 0)
            {
                tree[root].right = node;
                return;
            }
            insert(tree, tree[root].right, node);
        }
    }
};
