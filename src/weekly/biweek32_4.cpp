
#include <string>
#include <vector>

using namespace std;


class Solution {
public:
    int longestAwesome(string s) {
        int n = s.size();

    }
};


class Solution_2 {
public:
    int longestAwesome(string s) {
        int n = s.size();
        vector<int> cnt(10, 0);
        for(int i = 0; i < n; ++i)
        {
            ++cnt[s[i] - '0'];
        }
        return left;
    }

private:
    bool check(const string& s, int mid)
    {
        int n = s.size();
        vector<int> cnt(10, 0);
        for(int i = 0; i < mid; ++i)
            ++cnt[s[i] - '0'];
        if(check2(cnt))
            return true;
        for(int i = mid; i < n; ++i)
        {
            --cnt[s[i - mid] - '0'];
            ++cnt[s[i] - '0'];
            if(check2(cnt))
                return true;
        }
        return false;
    }

    bool check2(const vector<int>& cnt)
    {
        bool flag = false;
        for(int i = 0; i <= 9; ++i)
        {
            if((cnt[i] & 1) == 0)
                continue;
            if(flag)
                return false;
            flag = true;
        }
        return true;
    }
};


