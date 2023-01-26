// prob420: Strong Password Checker

/*
 * https://leetcode-cn.com/problems/strong-password-checker/
 */

#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    int strongPasswordChecker(string s) {
        // 小写，大写，数字缺少的种类数，可以改或者插入
        int miss = check_miss(s);
        // k3[0] := 3n 型的各个长度
        // k3[1] := 3n + 1 型的各个长度
        // k3[2] := 3n + 2 型的各个长度
        vector<vector<int>> k3 = check3(s);

        int n = s.size();

        if(n < 6)
        {
            return max(6 - n, miss);
        }
        else
        {
            int k3_all = 0;
            for(auto i: k3)
                for(int len: i)
                    k3_all += len / 3;
            if(n <= 20)
                return max(miss, k3_all);
            else
            {
                // 如果全都用替换，解决所有三连串需要 k3_all 步
                // 下面看至少要做的 n - 20 步删除可以替换几步
                int N = n - 20; // 解决长度溢出的删除次数
                // 先替换 3n 型, 一次删除可以抵一次替换
                while(!k3[0].empty() && N > 0)
                {
                    int len = k3[0].back();
                    --N;
                    k3[0].pop_back();
                    --k3_all;
                    if(len - 1 >= 3)
                        k3[2].push_back(len - 1);
                }
                // 再替换 3n + 1 型，2 次删除可以抵 1 次替换
                while(!k3[1].empty() && N > 1)
                {
                    int len = k3[1].back();
                    N -= 2;
                    k3[1].pop_back();
                    --k3_all;
                    if(len - 2 >= 3)
                        k3[2].push_back(len - 2);
                }
                // 最后替换 3n + 1 型，3 次删除可以抵 1 次替换
                while(!k3[2].empty() && N > 2)
                {
                    int len = k3[2].back();
                    N -= 3;
                    --k3_all;
                    if(len - 3 >= 5)
                        k3[2].back() -= 3;
                    else
                        k3[2].pop_back();
                }
                // 如果是 empty 退出的而不是 N 耗尽，
                // 则 n - 20 的删除将处理三连串所需的改操作全都抵扣了
                return n - 20 + max(k3_all, miss);
            }
        }
    }

private:
    int check_miss(const string& s)
    {
        bool f1 = 1, f2 = 1, f3 = 1;
        for(const char &ch: s)
        {
            if(ch >= 'A' && ch <= 'Z')
                f1 = 0;
            if(ch >= 'a' && ch <= 'z')
                f2 = 0;
            if(ch >= '0' && ch <= '9')
                f3 = 0;
            if(f1 + f2 + f3 == 0)
                break;
        }
        return f1 +  f2 + f3;
    }

    vector<vector<int>> check3(const string& s)
    {
        int n = s.size();
        int i = 0;
        vector<vector<int>> result(3);
        while(i < n)
        {
            char ch = s[i];
            int j = i;
            while(j < n && s[j] == ch)
                ++j;
            int len = j - i;
            if(len >= 3)
                result[len % 3].push_back(len);
            i = j;
        }
        return result;
    }
};
