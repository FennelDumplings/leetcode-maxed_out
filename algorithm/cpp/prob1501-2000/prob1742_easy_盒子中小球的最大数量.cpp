#include <unordered_map>

using namespace std;

class Solution {
public:
    int countBalls(int lowLimit, int highLimit) {
        unordered_map<int, int> mapping;
        int ans = 0;
        for(int i = lowLimit; i <= highLimit; ++i)
        {
            int cnt = ++mapping[digit_sum(i)];
            ans = max(ans, cnt);
        }
        return ans;
    }

    int digit_sum(int x)
    {
        int ans = 0;
        while(x)
        {
            ans += (x % 10);
            x /= 10;
        }
        return ans;
    }
};
