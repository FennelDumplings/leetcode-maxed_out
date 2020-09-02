

#include <vector>

using namespace std;

class Solution {
public:
    bool threeConsecutiveOdds(vector<int>& arr) {
        int n = arr.size();
        if(n < 3) return false;
        for(int i = 2; i < n; ++i)
            if((arr[i] & 1) && (arr[i - 1] & 1) && (arr[i - 2] & 1))
                return true;
        return false;
    }
};
