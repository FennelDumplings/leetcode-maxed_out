
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
public:
    vector<int> findingUsersActiveMinutes(vector<vector<int>>& logs, int k) {
        unordered_map<int, unordered_set<int>> mapping; // maping[id] -> 活跃分钟列表
        for(const vector<int> &record: logs)
        {
            int id = record[0];
            int time = record[1];
            mapping[id].insert(time);
        }
        vector<int> result(k, 0);
        for(auto item: mapping)
        {
            ++result[item.second.size() - 1];
        }
        return result;
    }
};
