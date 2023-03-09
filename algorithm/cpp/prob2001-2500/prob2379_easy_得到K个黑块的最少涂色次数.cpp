class Solution {
public:
    int minimumRecolors(string blocks, int k) {
        int n = blocks.size();
        int ans = 0;
        for(int i = 0; i < k; ++i)
        {
            ans += blocks[i] == 'W';
        }
        int s = ans;
        for(int i = k; i < n; ++i)
        {
            s -= blocks[i - k] == 'W';
            s += blocks[i] == 'W';
            ans = min(ans, s);
        }
        return ans;
    }
};
