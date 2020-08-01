
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    int minFlips(string target) {
        if(target.empty()) return 0;
        int cnt = 0;
        int n = target.size();
        char prev = '0';
        for(int i = 0; i < n; ++i)
        {
            if(target[i] != prev)
                ++cnt;
            prev = target[i];
        }
        return cnt;
    }
};
