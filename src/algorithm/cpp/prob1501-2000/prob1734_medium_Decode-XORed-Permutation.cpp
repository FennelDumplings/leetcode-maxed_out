#include <vector>

using namespace std;

class Solution {
public:
    vector<int> decode(vector<int>& encoded) {
        int n = encoded.size() + 1;
        if(n == 2) return vector<int>{1, 2};
        vector<int> perm(n);
        int x = 0;
        for(int a = 1; a <= n; ++a)
            x ^= a;
        int y = 0;
        for(int i = 1; i < n; i += 2)
            y ^= encoded[i];
        perm[0] = x ^ y;
        for(int i = 1; i < n; ++i)
            perm[i] = perm[i - 1] ^ encoded[i - 1];
        return perm;
    }
};
