// 20200705
// 2.

#include <vector>

using namespace std;

class Solution {
public:
    int getLastMoment(int n, vector<int>& left, vector<int>& right) {
        int max_left = 0;
        for(int i: left)
            max_left = max(max_left, i);
        int min_right = n;
        for(int i: right)
            min_right = min(min_right, i);
        return max(n - min_right, max_left);
    }
};
