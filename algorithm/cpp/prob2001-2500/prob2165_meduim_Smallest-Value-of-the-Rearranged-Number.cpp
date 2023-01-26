
class Solution {
public:
    long long smallestNumber(long long num) {
        if(num == 0)
            return 0;
        vector<int> digits;
        int sign = 1;
        if(num < 0)
        {
            sign = -1;
            num = -num;
        }
        int n_zero = 0;
        while(num != 0)
        {
            if(num % 10 == 0)
                ++n_zero;
            digits.push_back(num % 10);
            num /= 10;
        }
        int m = digits.size();
        sort(digits.begin(), digits.end());
        if(sign == 1)
            swap(digits[n_zero], digits[0]);
        else
            reverse(digits.begin(), digits.end());
        long long ans = 0;
        for(int i = 0; i < m; ++i)
        {
            ans *= 10;
            ans += digits[i];
        }
        ans *= sign;
        return ans;
    }
};
