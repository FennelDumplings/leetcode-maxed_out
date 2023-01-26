#include <vector>
#include <unordered_map>

using namaspace std;

class Solution {
public:
    int sumOfUnique(vector<int>& nums) {
        unordered_map<int, bool> mapping;
        for(int x: nums)
        {
            if(mapping.count(x) == 0)
                mapping[x] = false;
            else
                mapping[x] = true;
        }
        int ans = 0;
        for(auto x: mapping)
        {
            if(!x.second)
                ans += x.first;
        }
        return ans;
    }
};
