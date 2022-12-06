class Solution {
public:
    int numDifferentIntegers(string word) {
        int n = word.size();
        int ans = 0;
        unordered_set<int> setting;
        int left = 0;
        while(left < n)
        {
            int right = left;
            int x = 0;
            while(right < n)
            {
                int digit = word[right] - '0';
                if(digit > 9 || digit < 0)
                    break;
                x *= 10;
                x += digit;
            }
            if(right == left)
            {
                left++;
                continue;
            }
            if(setting.count(x) == 0)
            {
                ans++;
                setting.insert(x);
            }
            left = right;
        }
        return ans;
    }
};
