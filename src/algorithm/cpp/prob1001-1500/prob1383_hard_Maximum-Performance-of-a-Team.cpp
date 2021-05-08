// prob1383: Maximum Performance of a Team

/*
 * There are n engineers numbered from 1 to n and two arrays: speed and efficiency, where speed[i] and efficiency[i]
 * represent the speed and efficiency for the i-th engineer respectively. Return the maximum performance of a team
 * composed of at most k engineers, since the answer can be a huge number, return this modulo 10^9 + 7.
 * The performance of a team is the sum of their engineers' speeds multiplied by the minimum efficiency among their engineers. 
 */

/*
 * Example 1:
 * Input: n = 6, speed = [2,10,3,1,5,8], efficiency = [5,4,3,9,7,2], k = 2
 * Output: 60
 * Explanation:
 * We have the maximum performance of the team by selecting engineer 2 (with speed=10 and efficiency=4) and engineer 5 (with speed=5 and efficiency=7). That is, performance = (10 + 5) * min(4, 7) = 60.
 * Example 2:
 * Input: n = 6, speed = [2,10,3,1,5,8], efficiency = [5,4,3,9,7,2], k = 3
 * Output: 68
 * Explanation:
 * This is the same example as the first but k = 3. We can select engineer 1, engineer 2 and engineer 5 to get the maximum performance of the team. That is, performance = (2 + 10 + 5) * min(5, 4, 7) = 68.
 * Example 3:
 * Input: n = 6, speed = [2,10,3,1,5,8], efficiency = [5,4,3,9,7,2], k = 4
 * Output: 72
 */

/*
 * Constraints:
 * 1 <= n <= 10^5
 * speed.length == n
 * efficiency.length == n
 * 1 <= speed[i] <= 10^5
 * 1 <= efficiency[i] <= 10^8
 * 1 <= k <= n
 */

#include <queue>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

class Solution {
public:
    int maxPerformance(int n, vector<int>& speed, vector<int>& efficiency, int k) {
        vector<Engineer> engineers;
        for(int i = 0; i < n; ++i)
            engineers.push_back(Engineer(speed[i], efficiency[i]));
        sort(engineers.begin(), engineers.end(), Cmp());
        ll result = 0;
        ll sum = 0;
        int min_efficiency = INT_MAX;
        priority_queue<int, vector<int>, greater<int> > pq;
        for(int i = 0; i < n; ++i)
        {
            min_efficiency = min(min_efficiency, engineers[i].efficiency);
            pq.push(engineers[i].speed);
            sum += engineers[i].speed;
            if((int)pq.size() > k)
            {
                sum -= pq.top();
                pq.pop();
            }
            result = max(result, sum * min_efficiency);
        }
        return result % MOD;
    }

private:
    using ll = long long;
    const int MOD = 1e9 + 7;

    struct Engineer
    {
        int speed, efficiency;
        Engineer(int s, int e):speed(s),efficiency(e){}
    };

    struct Cmp
    {
        bool operator()(const Engineer& engineer1, const Engineer& engineer2)
        {
            if(engineer1.efficiency == engineer2.efficiency)
                return engineer1.speed > engineer2.speed;
            return engineer1.efficiency > engineer2.efficiency;
        }
    };
};
