// prob1640: Check Array Formation Through Concatenation

/*
 * https://leetcode-cn.com/problems/check-array-formation-through-concatenation/
 */

#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    bool canFormArray(vector<int>& arr, vector<vector<int>>& pieces) {
        unordered_map<int, vector<int>> mapping;
        int m = pieces.size();
        for(int i = 0; i < m; ++i)
        {
            mapping[pieces[i][0]] = pieces[i];
        }
        int i = 0;
        int n = arr.size();
        while(i < n)
        {
            int h = arr[i];
            if(mapping.count(h) == 0)
                return false;
            int j = 0;
            int m = mapping[h].size();
            while(j < m)
            {
                if(arr[i] != mapping[h][j])
                    return false;
                ++i;
                ++j;
            }
            mapping.erase(h);
        }
        return mapping.empty();
    }
};
