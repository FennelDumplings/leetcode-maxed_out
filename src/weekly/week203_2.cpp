
#include <algorithm>
#include <vector>

using namespace std;

class Solution {
public:
    int maxCoins(vector<int>& piles) {
        sort(piles.begin(), piles.end());
        int n = piles.size();
        int cnt = 0;
        int ans = 0;
        for(int i = n - 2; i >= 0; i -= 2)
        {
            ++cnt;
            if(cnt > n / 3)
                break;
            ans += piles[i];
        }
        return ans;
    }
};
