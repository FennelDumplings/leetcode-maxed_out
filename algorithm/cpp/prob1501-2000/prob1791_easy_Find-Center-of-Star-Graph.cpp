#include <vector>

using namespace std;

class Solution {
public:
    int findCenter(vector<vector<int>>& edges) {
        int x1 = edges[0][0];
        int x2 = edges[0][1];
        int x3 = edges[1][0];
        int x4 = edges[1][1];
        if(x3 == x1 || x3 == x2)
            return x3;
        else
            return x4;
    }
};
