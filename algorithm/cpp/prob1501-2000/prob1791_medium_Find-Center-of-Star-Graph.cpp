
#include <string>
#include <vector>
#include <unordered_set>

using namespace std;

class Solution {
public:
    int findCenter(vector<vector<int>>& edges) {
        unordered_set<int> setting;
        for(const vector<int>& edge: edges)
        {
            if(setting.count(edge[0]) > 0)
                return edge[0];
            else
                setting.insert(edge[0]);
            if(setting.count(edge[1]) > 0)
                return edge[1];
            else
                setting.insert(edge[1]);
        }
        return -1;
    }
};
