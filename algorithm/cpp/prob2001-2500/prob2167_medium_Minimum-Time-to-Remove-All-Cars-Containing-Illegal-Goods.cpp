#include <string>
#include <climits>

using namespace std;

class Solution {
public:
    int minimumTime(string s) {
        int n = s.size();
        int x = n;
        int sums = 0;
        int ans = INT_MAX;
        for(int j = 0; j < n; ++j)
        {
            x = min(x, j - 2 * sums);
            sums += s[j] - '0';
            ans = min(ans, x + 2 * sums - j);
        }
        return min(ans + n - 1, n);
    }
};
