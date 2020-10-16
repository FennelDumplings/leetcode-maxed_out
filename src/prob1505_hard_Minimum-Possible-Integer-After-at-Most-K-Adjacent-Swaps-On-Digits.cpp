// prob1505: Minimum Possible Integer After at Most K Adjacent Swaps On Digits

/*
 * https://leetcode-cn.com/problems/minimum-possible-integer-after-at-most-k-adjacent-swaps-on-digits/
 */

#include <vector>
#include <string>

using namespace std;

class Solution_2 {
public:
    string minInteger(string num, int k) {
        int n = num.size();
        int i = 0;
        while(i < n && k > 0)
        {
            for(char t = '0'; t <= '9'; ++t)
            {
                // 问：[i..n-1] 中最小的 j 是多少，num[j] == t，若不存在，j == n
                int j = i;
                while(j < n && num[j] != t)
                    ++j;
                if(j < n && j - i <= k)
                {
                    k -= j - i;
                    for(int k = j; k > i; --k)
                        num[k] = num[k - 1];
                    num[i] = t;
                    break;
                }
            }
            ++i;
        }
        return num;
    }
};

// BIT
#include <list>

class BIT
{
public:
    BIT(){}
    BIT(int n)
    {
        vec = vector<int>(n + 1);
    }

    void add(int idx, int delta)
    {
        // idx 位置加 delta，BIT 中在 vec[idx + 1] 做改动
        for(int i = idx + 1; i < (int)vec.size(); i += lowbit(i))
            vec[i] += delta;
    }

    int query(int idx)
    {
        if(idx <= 0)
            return 0;
        // [0..idx] 的和
        // 返回 bit 中 [1..idx+1] 的和
        int ans = 0;
        for(int i = idx + 1; i > 0; i -= lowbit(i))
            ans += vec[i];
        return ans;
    }

private:
    vector<int> vec;

    int lowbit(int x)
    {
        return x & (-x);
    }
};

class Solution {
public:
    string minInteger(string num, int k) {
        int n = num.size();
        BIT bit(n);
        string result;
        vector<list<int>> pos(10);
        for(int i = 0; i < n; ++i)
            pos[num[i] - '0'].push_back(i);
        for(int i = 0; i < n; ++i)
        {
            for(char t = '0'; t <= '9'; ++t)
            {
                // [i..n-1] 中最小的满足 num[j]==t 的 j 或不存在
                if(!pos[t - '0'].empty())
                {
                    int j = pos[t - '0'].front();
                    // [j..n-1] 中交换的次数
                    int d = j - i + bit.query(n - 1) - bit.query(j);
                    if(d <= k)
                    {
                        k -= d;
                        pos[t - '0'].erase(pos[t - '0'].begin());
                        bit.add(j, 1);
                        result += t;
                        break;
                    }
                }
            }
        }
        return result;
    }
};
