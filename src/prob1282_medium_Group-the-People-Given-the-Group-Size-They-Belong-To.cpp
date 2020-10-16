// prob1282: Group the People Given the Group Size They Belong To

/*
 * https://leetcode-cn.com/problems/group-the-people-given-the-group-size-they-belong-to/
 */

#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    vector<vector<int>> groupThePeople(vector<int>& groupSizes) {
        unordered_map<int, vector<int>> mapping;
        int n = groupSizes.size();
        for(int i = 0; i < n; ++i)
            mapping[groupSizes[i]].push_back(i);
        vector<vector<int>> result;
        for(auto &item: mapping)
        {
            int k = item.second.size() / item.first;
            for(int i = 0; i < k; ++i)
                result.push_back(vector<int>(item.second.begin() + item.first * i, item.second.begin() + item.first * (i + 1)));
        }
        return result;
    }
};
