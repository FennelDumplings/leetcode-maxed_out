// prob475: Heaters

/*
 * Winter is coming! Your first job during the contest is to design a standard heater with fixed warm radius to warm all the houses.
 * Now, you are given positions of houses and heaters on a horizontal line, find out minimum radius of heaters so that all houses could be covered by those heaters.
 * So, your input will be the positions of houses and heaters seperately, and your expected output will be the minimum radius standard of heaters.
 */

/*
 * Note:
 * Numbers of houses and heaters you are given are non-negative and will not exceed 25000.
 * Positions of houses and heaters you are given are non-negative and will not exceed 10^9.
 * As long as a house is in the heaters' warm radius range, it can be warmed.
 * All the heaters follow your radius standard and the warm radius will the same.
 */

/*
 * Example 1:
 * Input: [1,2,3],[2]
 * Output: 1
 * Explanation: The only heater was placed in the position 2, and if we use the radius 1 standard, then all the houses can be warmed.
 * Example 2:
 * Input: [1,2,3,4],[1,4]
 * Output: 1
 * Explanation: The two heater was placed in the position 1 and 4. We need to use radius 1 standard, then all the houses can be warmed.
 */

#include <vector>
#include <deque>
#include <algorithm>
#include <climits>

using namespace std;

// 栈
class Solution {
public:
    int findRadius(vector<int>& houses, vector<int>& heaters) {
        int n = houses.size();
        int m = heaters.size();
        deque<int> deq;
        sort(houses.begin(), houses.end());
        sort(heaters.begin(), heaters.end());
        int result = heaters[0] > houses[0] ? heaters[0] - houses[0] : 0;

        int i = 0, j = 0;
        while(i < n && houses[i] <= heaters[j])
            ++i;
        deq.push_back(j);
        ++j;
        while(i < n && j < m)
        {
            if(houses[i] <= heaters[j])
            {
                deq.push_back(i);
                ++i;
            }
            else
            {
                while(deq.size() > 1)
                {
                    int dist = min(heaters[j] - houses[deq.back()], houses[deq.back()] - heaters[deq.front()]);
                    deq.pop_back();
                    result = max(result, dist);
                }
                deq.pop_back();
                deq.push_back(j);
                ++j;
            }
        }
        if(j == m)
            result = max(result, houses[n - 1] - heaters[deq.front()]);
        if(i == n)
        {
            while(deq.size() > 1)
            {
                int dist = min(heaters[j] - houses[deq.back()], houses[deq.back()] - heaters[deq.front()]);
                deq.pop_back();
                result = max(result, dist);
            }
        }
        return result;
    }
};

// 二分
class Solution_2 {
public:
    int findRadius(vector<int>& houses, vector<int>& heaters) {
        heaters.push_back(INT_MIN), heaters.push_back(INT_MAX);
        sort(heaters.begin(), heaters.end());
        int result = 0;
        for(auto &x: houses)
        {
            int l = 0, r = heaters.size() - 1;
            while(l < r)
            {
                int mid = (l + r) / 2;
                if(heaters[mid] >= x)
                    r = mid;
                else
                    l = mid + 1;
            }
            result = max(result, (int)min(heaters[r] - 0ll - x, x - 0ll - heaters[r - 1]));
        }
        return result;
    }
};
