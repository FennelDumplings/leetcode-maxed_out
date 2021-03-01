
#include <string>
#include <unordered_set>

using namespace std;

class Solution {
public:
    bool halvesAreAlike(string s) {
        int n = s.size();
        unordered_set<char> setting = {
            'a', 'e', 'i', 'o', 'u',
            'A', 'E', 'I', 'O', 'U',
        };
        int cnt1 = 0;
        for(int i = 0; i < n / 2; ++i)
        {
            char ch = s[i];
            if(setting.count(ch) > 0)
                ++cnt1;
        }
        int cnt2 = 0;
        for(int i = n / 2; i < n; ++i)
        {
            char ch = s[i];
            if(setting.count(ch) > 0)
                ++cnt2;
        }
        return cnt1 == cnt2;
    }
};
