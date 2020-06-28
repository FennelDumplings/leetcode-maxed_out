// 20200627
// 2.

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int kthFactor(int n, int k) {
        vector<int> factors;
        for(int i = 1; i * i <= n; ++i)
        {
            if(n % i == 0)
            {
                factors.push_back(i);
                if(n / i != i)
                    factors.push_back(n / i);
            }
        }
        if((int)factors.size() < k)
            return -1;
        sort(factors.begin(), factors.end());
        return factors[k - 1];
    }
};
