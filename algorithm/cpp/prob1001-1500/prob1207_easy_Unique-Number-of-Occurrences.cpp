// prob1207: Unique Number of Occurrences

/*
 * https://leetcode-cn.com/problems/unique-number-of-occurrences/
 */

#include <vector>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class Solution {
public:
    bool uniqueOccurrences(vector<int>& arr) {
        unordered_map<int, int> mapping;
        for(int i: arr)
            ++mapping[i];
        unordered_set<int> setting;
        for(auto record: mapping)
        {
            if(setting.count(record.second) > 0)
                return false;
            setting.insert(record.second);
        }
        return true;
    }
};
