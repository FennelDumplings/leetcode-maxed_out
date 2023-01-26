// prob881: Boats to Save People

/*
 * https://leetcode-cn.com/problems/boats-to-save-people/
 */

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int numRescueBoats(vector<int>& people, int limit) {
        sort(people.begin(), people.end());
        int n = people.size();
        int left = 0, right = n - 1;
        int ans = 0;
        while(left <= right)
        {
            ++ans;
            if(limit - people[right] >= people[left])
                ++left;
            --right;
        }
        return ans;
    }
};
