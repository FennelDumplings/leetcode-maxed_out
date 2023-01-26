// prob1086: High Five

/*
 * https://leetcode-cn.com/problems/high-five/
 */

#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

class Solution {
public:
    vector<vector<int>> highFive(vector<vector<int>>& items) {
        const int max_id = 1000;
        vector<vector<int>> students(max_id + 1);
        for(vector<int> &r: items)
            students[r[0]].push_back(r[1]);
        vector<vector<int>> result;
        for(int id = 1; id <= max_id; ++id)
        {
            vector<int> &scores = students[id];
            if(scores.empty())
                continue;
            nth_element(scores.begin(), scores.begin() + 5, scores.end(), greater<int>());
            int sum = 0;
            for(int i = 0; i < 5; ++i)
                sum += scores[i];
            result.push_back({id, sum / 5});
        }
        return result;
    }
};
