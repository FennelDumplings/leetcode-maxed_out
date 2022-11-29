class Solution {
public:
    int minOperations(string s) {
        int n = s.size();
        int cnt01 = 0;
        int cnt10 = 0;
        for(int i = 0; i < n; ++i)
        {
            if((i & 1) == 0)
            {
                cnt01 += s[i] == '1';
                cnt10 += s[i] == '0';
            }
            else
            {
                cnt01 += s[i] == '0';
                cnt10 += s[i] == '1';
            }
        }
        int ans = cnt01;
        if(cnt01 > cnt10)
            ans = cnt10;
        return ans;
    }
};
