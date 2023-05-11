class Solution {
public:
    bool queryString(string s, int n) {
        int m = s.size();
        int k = bit_length(n) - 1;
        if(m < k + pow(2, k-1) - 1)
            return false;
        if(m < k + 1 + n - pow(2, k))
            return false;
        if(!sliding_window(s, k + 1, pow(2, k), n))
            return false;
        if(!sliding_window(s, k, pow(2, k - 1), pow(2, k) - 1))
            return false;
        return true;
    }

    bool sliding_window(const string& s, const int len, const int left, const int right)
    {
        // 长为 len 的滑动窗口扫描 s 一轮，看 [left, right] 是否都取到了
        int num = 0; // 窗口的二进制表示的整数
        int m = s.size();
        // 第一个窗口
        for(int i = 0; i < len; ++i)
        {
            num <<= 1;
            num += s[i] - '0';
        }
        unordered_set<int> setting;
        if(num >= left && num <= right)
            setting.insert(num);
        int mask = (1 << len) - 1;
        for(int i = len; i < m; ++i)
        {
            num <<= 1;
            num &= mask;
            num += s[i] - '0';
            if(num >= left && num <= right)
                setting.insert(num);
        }
        return setting.size() == right - left + 1;
    }

    int bit_length(int n)
    {
        int len = 0;
        while(n)
        {
            len++;
            n >>= 1;
        }
        return len;
    }
};
