// prob60: Permutation Sequence

/*
 * The set [1,2,3,...,n] contains a total of n! unique permutations.
 * By listing and labeling all of the permutations in order, we get the following sequence for n = 3:
 * "123"
 * "132"
 * "213"
 * "231"
 * "312"
 * "321"
 * Given n and k, return the kth permutation sequence.
 * Note:
 * Given n will be between 1 and 9 inclusive.
 * Given k will be between 1 and n! inclusive.
 */

/*
 * Example 1:
 * Input: n = 3, k = 3
 * Output: "213"
 * Example 2:
 * Input: n = 4, k = 9
 * Output: "2314"
 */

#include <string>
#include <vector>
#include <list>

using namespace std;

// DFS
class Solution {
public:
    string getPermutation(int n, int k) {
        if(n == 1) return "1";
        string result = "";
        // 第0个一定是 '1'
        string path = "";
        int state = 0;
        int deep = 0;
        dfs(deep, path, 0, result, k, n, state);
        return result;
    }

private:
    bool dfs(int& deep, string& path, int i, string& result, int k, int n, int& state)
    {
        // 已经产生 deep 个序列，当前序列已选 i 个数字
        if(i == n)
        {
            ++deep;
            if(deep == k)
            {
                result = path;
                return true;
            }
            else
                return false;
        }

        for(int j = 1; j <= n; ++j)
        {
            if(!(((1 << j) & state))) // 数字 j 没选
            {
                path += '0' + j;
                state |= (1 << j);
                if(dfs(deep, path, i + 1, result, k, n, state))
                    return true;
                path.pop_back();
                state &= ~(1 << j);
            }
        }
        return false;
    }
};

// dfs，用数字做，比带着字符串做快一倍
class Solution_2 {
public:
    string getPermutation(int n, int k) {
        if(n == 1) return "1";
        int result = 0;
        // 第0个一定是 '1'
        int path = 0;
        int state = 0;
        int deep = 0;
        dfs(deep, path, 0, result, k, n, state);
        return to_string(result);
    }

private:
    bool dfs(int& deep, int& path, int i, int& result, int k, int n, int& state)
    {
        // 已经产生 deep 个序列，当前序列已选 i 个数字
        if(i == n)
        {
            ++deep;
            if(deep == k)
            {
                result = path;
                return true;
            }
            else
                return false;
        }

        for(int j = 1; j <= n; ++j)
        {
            if(!(((1 << j) & state))) // 数字 j 没选
            {
                path = path * 10 + j;
                state |= (1 << j);
                if(dfs(deep, path, i + 1, result, k, n, state))
                    return true;
                path = (path - j) / 10;
                state &= ~(1 << j);
            }
        }
        return false;
    }
};

// 阶乘数系统
// 从高位往低位选
class Solution_3 {
public:
    string getPermutation(int n, int k) {
        vector<int> nums(n, 0);
        vector<int> factorials(n, 1);
        for(int i = 0; i < n; ++i) nums[i] = i + 1;
        for(int i = 1; i < n; ++i) factorials[i] = factorials[i - 1] * i;

        // fit k in the invertal 0 .. (n! - 1)
        --k; // 从零计数
        int ans = 0;
        for(int i = n - 1; i >= 0; --i) // 从高位往低位选
        {
            int idx = k / factorials[i];
            k -= idx * factorials[i];
            ans = ans * 10 + nums[idx];
            nums.erase(nums.begin() + idx);
        }
        return to_string(ans);
    }
};

// 加剪枝的 DFS
// 在 Solution_2 基础上优化
class Solution_4 {
public:
    string getPermutation(int n, int k) {
        if(n == 1) return "1";
        vector<int> factorials(n + 1, 1);
        for(int i = 2; i <= n; ++i) factorials[i] = factorials[i - 1] * i;
        int result = 0;
        // 第0个一定是 '1'
        int path = 0;
        int state = 0;
        int deep = 0;
        dfs(deep, path, 0, result, k, n, state, factorials);
        return to_string(result);
    }

private:
    bool dfs(int& deep, int& path, int i, int& result, int k, int n, int& state, const vector<int>& factorials)
    {
        // 剪枝
        // 已经选了 i 个数 还剩 n - i 个数，共 factorials[n - i] 种
        if(deep + factorials[n - i] < k)
        {
            deep += factorials[n - i];
            return false;
        }
        // 已经产生 deep 个序列，当前序列已选 i 个数字
        if(i == n)
        {
            ++deep;
            if(deep == k)
            {
                result = path;
                return true;
            }
            else
                return false;
        }

        for(int j = 1; j <= n; ++j)
        {
            if(!(((1 << j) & state))) // 数字 j 没选
            {
                path = path * 10 + j;
                state |= (1 << j);
                if(dfs(deep, path, i + 1, result, k, n, state, factorials))
                    return true;
                path = (path - j) / 10;
                state &= ~(1 << j);
            }
        }
        return false;
    }
};

// DFS + 剪枝 可以用双链表模拟
class Solution_5 {
public:
    string getPermutation(int n, int k) {
        if(n == 1) return "1";
        --k; // 从 n 个数字全排列中找到索引为 k - 1 的
        vector<int> factorials(n + 1, 1);
        for(int i = 2; i <= n; ++i) factorials[i] = factorials[i - 1] * i;
        int result = 0;
        list<int> nums(n, 0);
        auto iter = nums.begin();
        for(int i = 0; iter != nums.end(); ++iter, ++i)
            *iter = i + 1;

        // i: 剩余数字个数
        for(int i = n - 1; i >= 0; --i)
        {
            int index = k / factorials[i];
            iter = _get_iter(nums, index);
            result = result * 10 + *iter;
            nums.erase(iter);
            k -= index * factorials[i];
        }
        return to_string(result);
    }

private:
    list<int>::iterator _get_iter(list<int>& l, int k)
    {
        auto iter = l.begin();
        while(k)
        {
            ++iter;
            --k;
        }
        return iter;
    }
};


// Cantor unfolds
class Solution_6 {
public:
    string getPermutation(int n, int k) {
        vector<int> nums(n, 0);
        vector<int> factorials(n, 1);
        for(int i = 0; i < n; ++i) nums[i] = i + 1;
        for(int i = 1; i < n; ++i) factorials[i] = factorials[i - 1] * i;

        // fit k in the invertal 0 .. (n! - 1)
        --k; // 从零计数
        int ans = 0;
        for(int i = n - 1; i >= 0; --i) // 从高位往低位选
        {
            int idx = k / factorials[i];
            k -= idx * factorials[i];
            ans = ans * 10 + nums[idx];
            nums.erase(nums.begin() + idx);
        }
        return to_string(ans);
    }
};
