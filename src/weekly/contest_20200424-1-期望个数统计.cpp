
#include <vector>

using namespace std;

class Solution {
public:
    int expectNumber(vector<int>& scores) {
        vector<int> cnt(1e6 + 1, 0);
        for(const int &score: scores)
            ++cnt[score];
        int result = 0;
        for(const int &a: cnt)
            if(a != 0)
                ++result;
        return result;
    }
};
