// prob679: 24 Game

/*
 * https://leetcode-cn.com/problems/24-game/
 */

#include <vector>
#include <algorithm>

using namespace std;

struct Frac
{
    // a / b
    // 上游要保证 b != 0
    int a, b;
    int operator()()
    {
        if(b == 0) return -1;
        if(a == 0) return 0;
        if(a % b != 0) return -1;
        return a / b;
    }
    Frac(int a=0, int b=1):a(a),b(b){}
    Frac operator+(const Frac& f) const
    {
        Frac res(a, b);
        if(b == f.b)
            res.a += f.a;
        else
        {
            res.b *= f.b;
            res.a *= f.b;
            res.a += f.a * b;
        }
        return res;
    }
    Frac operator-(const Frac& f) const
    {
        Frac res(a, b);
        if(b == f.b)
            res.a -= f.a;
        else
        {
            res.b *= f.b;
            res.a *= f.b;
            res.a -= f.a * b;
        }
        return res;
    }
    Frac operator*(const Frac& f) const
    {
        Frac res(a, b);
        res.a = a * f.a;
        res.b = b * f.b;
        return res;
    }
    Frac operator/(const Frac& f) const
    {
        Frac res(a, b);
        res.a = a * f.b;
        res.b = b * f.a;
        return res;
    }
};

class Solution {
public:
    bool judgePoint24(vector<int>& nums) {
        vector<int> ops(3, -1);
        // ops[i] :
        // 1: +
        // 2: -
        // 3: *
        // 4: /
        sort(nums.begin(), nums.end());
        do{
            if(dfs(nums, 0, ops))
                return true;
        }
        while(next_permutation(nums.begin(), nums.end()));
        return false;
    }

private:
    int order[5][3] = {
        {0, 1, 2},
        {0, 2, 1},
        {1, 0, 2},
        {1, 2, 0},
        {2, 1, 0}
    };

    bool dfs(const vector<int>& nums, int pos, vector<int>& ops)
    {
        int n = nums.size();
        if(pos == n - 1)
        {
            return check(nums, ops);
        }
        for(int op = 1; op <= 4; ++op)
        {
            ops[pos] = op;
            if(dfs(nums, pos + 1, ops))
                return true;
        }
        return false;
    }

    bool check(const vector<int>& nums, const vector<int>& ops)
    {
        vector<Frac> fracs;
        for(int i: nums)
            fracs.push_back(Frac(i, 1));
        for(int i = 0; i < 5; ++i)
        {
            int ord[3];
            for(int j = 0; j < 3; ++j)
                ord[j] = order[i][j];
            if(_check(fracs, ops, ord))
                return true;
        }
        return false;
    }

    bool _check(vector<Frac> fracs, vector<int> ops, int ord[])
    {
        bool flag = ord[0] == 0 && ord[1] == 2 && ord[2] == 1;
        flag = flag && ops[ord[0]] == 2 && ops[ord[1]] == 2 && ops[ord[2]] == 3;
        for(int i = 0; i < 3; ++i)
        {
            int pos = ord[i];
            int op = ops[pos];
            Frac left = fracs[pos];
            Frac right = fracs[pos + 1];
            if(op == 4 && right() == 0)
                continue;
            Frac middle = calc(left, right, op);
            fracs[pos] = middle;
            fracs.erase(fracs.begin() + pos + 1);
            ops.erase(ops.begin() + pos);
            for(int j = i + 1; j < 3; ++j)
                if(ord[j] > ord[i])
                    --ord[j];
        }
        int ans = fracs[0]();
        return ans == 24;
    }

    Frac calc(Frac left, Frac right, int op)
    {
        if(op == 1)
            return left + right;
        else if(op == 2)
            return left - right;
        else if(op == 3)
            return left * right;
        else
            return left / right;
    }
};
