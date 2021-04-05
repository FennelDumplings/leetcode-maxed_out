
#include <vector>

using namespace std;

// class Solution {
// public:
//     int maxHappyGroups(int batchSize, vector<int>& groups) {
//         vector<int> cnt(batchSize);
//         for(int x: groups)
//         {
//             ++cnt[x % batchSize];
//         }
//         int ans = cnt[0];
//         for(int i = 1; i < (batchSize + 1) / 2; ++i)
//         {
//             ans += min(cnt[batchSize - i], cnt[i]) * 2;
//             cnt[batchSize - i] -= min(cnt[batchSize - i], cnt[i]);
//             cnt[i] -= min(cnt[batchSize - i], cnt[i]);
//         }
//         if(batchSize % 2 == 0)
//         {
//             ans += cnt[batchSize / 2] - (cnt[batchSize / 2] & 1);
//             cnt[batchSize / 2] = cnt[batchSize / 2] & 1;
//         }
//
//     }
// };

class Solution {
public:
    int maxHappyGroups(int batchSize, vector<int>& groups) {
        vector<int> cnt(batchSize);
        for(int x: groups)
            ++cnt[x % batchSize];
        int ans0 = cnt[0];

        int ans1 = 0;
        vector<int> seq;
        dfs(cnt, groups.size() - cnt[0], seq, ans1);
        return ans0 + ans1;
    }

private:
    void dfs(vector<int>& cnt, const int n, vector<int>& seq, int& ans1)
    {
        if((int)seq.size() == n)
        {
            ans1 = max(ans1, check(seq, (int)cnt.size()));
            return;
        }
        for(int x = 1; x < (int)cnt.size(); ++x)
        {
            if(cnt[x] == 0)
                continue;
            --cnt[x];
            seq.push_back(x);
            dfs(cnt, n, seq, ans1);
            seq.pop_back();
            ++cnt[x];
        }
    }

    int check(const vector<int>& seq, int batchSize)
    {
        int n = seq.size();
        int sum = 0;
        int ans = 0;
        for(int i = 0; i < n; ++i)
        {
            if(sum % batchSize == 0)
                ++ans;
            sum += seq[i];
        }
        return ans;
    }
};

// Zero🍋:
// 第四题python写起来优势很大
//
// Zero🍋:
// 可以直接拿tuple当下标
//
// Zero🍋:
// c++就得自己写hash
//
