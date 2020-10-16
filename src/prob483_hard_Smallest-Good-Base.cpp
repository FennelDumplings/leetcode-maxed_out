// prob483: Smallest Good Base

#include <string>
#include <sstream>
#include <algorithm>
#include <cmath>

using namespace std;

using ll = long long;

class Solution {
public:
    string smallestGoodBase(string n) {
        // 1e18 >= n >= 3
        ll N;
        stringstream ss;
        ss << n;
        ss >> N;
        int L = log2(N) + 1;
        while(L > 1)
        {
            ll l = 2, r = N - 1;
            while(l <= r)
            {
                ll mid = (l + r) / 2;
                int flag = check(L, mid, N);
                if(flag == 0)
                    return to_string(mid);
                else if(flag == 1)
                    l = mid + 1;
                else
                    r = mid - 1;
            }
            --L;
        }
        return to_string(-1);
    }

private:
    int check(int len, ll base, const ll N) {
        ll result = 1;
        ll p = 1;
        int l = 1;
        while(++l <= len)
        {
            p *= base;
            result += p;
            if(result > N)
                return -1;
            if(l < len && p > (N - result) / base)
                return -1;
        }
        if(result == N)
            return 0;
        return 1;
    }
};
