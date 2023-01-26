// prob1296: Divide Array in Sets of K Consecutive Numbers

/*
 * https://leetcode-cn.com/problems/divide-array-in-sets-of-k-consecutive-numbers/
 */

#include <vector>
#include <set>

using namespace std;

class Solution {
public:
    bool isPossibleDivide(vector<int>& nums, int k) {
        multiset<int> hands;
        for(int i: nums)
            hands.insert(i);
        if(hands.size() % k != 0)
            return false;
        while(!hands.empty())
        {
            int start = *hands.begin();
            hands.erase(hands.begin());
            for(int i = start + 1; i < start + k; ++i)
            {
                auto it = hands.find(i);
                if(it == hands.end())
                    return false;
                hands.erase(it);
            }
        }
        return true;
    }
};
