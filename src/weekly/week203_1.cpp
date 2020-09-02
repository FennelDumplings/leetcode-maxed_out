
#include <vector>

using namespace std;

class Solution {
public:
    vector<int> mostVisited(int n, vector<int>& rounds) {
        int N = rounds.size();
        vector<int> result;
        int start = rounds[0];
        int end = rounds[m];
        if(start == rounds[N - 1])
            return {start};
        else if(start < rounds[N - 1])
        {
            for(int i = start; i <= rounds[N - 1]; ++i)
                result.push_back(i);
        }
        else
        {
            for(int i = 1; i <= start; ++i)
                result.push_back(i);
            for(int i = rounds[N - 1]; i <= n; ++i)
            {
                result.push_back(i);
            }
        }
        return result;
    }
};
