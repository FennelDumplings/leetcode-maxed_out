// Prob849 Maximize Distance to Closest Person

/* Description:
 * In a row of seats, 1 represents a person sitting in that seat, and 0 represents that the seat is empty.
 * There is at least one empty seat, and at least one person sitting.
 * Alex wants to sit in the seat such that the distance between him and the closest person to him is maximized.
 * Return that maximum distance to closest person.
 */

/* Example:
 * Example 1:
 * Input: [1,0,0,0,1,0,1]
 * Output: 2
 * Explanation:
 * If Alex sits in the second open seat (seats[2]), then the closest person has distance 2.
 * If Alex sits in any other open seat, the closest person has distance 1.
 * Thus, the maximum distance to the closest person is 2.
 *
 * Example 2:
 * Example 2:
 * Input: [1,0,0,0]
 * Output: 3
 * Explanation:
 * If Alex sits in the last seat, the closest person is 3 seats away.
 * This is the maximum distance possible, so the answer is 3.
 */

/* Note:
 * 1 <= seats.length <= 20000
 * seats contains only 0s or 1s, at least one 0, and at least one 1.
 */

// Tags:

#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int maxDistToClosest(vector<int>& seats) {
        int n = seats.size();

        int left_side_0 = 0;
        int right_side_0 = 0;
        int left = 0;
        while(seats[left] == 0) ++left;
        left_side_0 = left;
        int right = n - 1;
        while(seats[right] == 0) --right;
        right_side_0 = n - 1 - right;
        int max_side_0 = max(left_side_0, right_side_0);

        int max_mid_0 = 0;
        while(left < right)
        {
            if(seats[left] == 1)
                ++left;
            else
            {
                int l = left;
                while(seats[l] == 0) ++l; // seats[right] == 1 且固定不动，所以l<right不用判断
                max_mid_0 = max(max_mid_0, l - left);
                left = l + 1;
            }
        }
        return max((max_mid_0 + 1) / 2, max_side_0);
    }
};

class Solution_2 {
public:
    int maxDistToClosest(vector<int>& seats) {
        int result = 0;
        int sum = 0;

        int left = 0;
        int right = seats.size() - 1;

        while(left != seats.size() && seats[left] == 0)
        {
            ++sum;
            ++left;
        }
        result = compare(result, sum, true);
        sum = 0;
        if(left == seats.size())
        {
            return result;
        }

        while(right != -1 && seats[right] == 0)
        {
            ++sum;
            --right;
        }
        result = compare(result, sum, true);
        sum = 0;
        if(right == -1)
        {
            return result;
        }

        while(left != right + 1)
        {
            if(seats[left] == 0)
            {
                ++sum;
            }
            else
            {
                result = compare(result, sum, false);
                sum = 0;
            }
            ++left;
        }
        return result;
    }

private:
    int compare(int result, int max_sum, bool side)
    {
        if(!side)
        {
            if((max_sum + 1) / 2 > result)
            {
                return (max_sum + 1) / 2;
            }
            else
            {
                return result;
            }
        }
        else
        {
            if(max_sum > result)
            {
                return max_sum;
            }
            else
            {
                return result;
            }
        }
    }
};


int main()
{
    int n;
    cout << "input n: " << endl;
    cin >> n;
    vector<int> vec(n, 0);
    for(auto iter = vec.begin(); iter != vec.end(); ++iter)
    {
        cin >> *iter;
    }
    for(auto iter = vec.begin(); iter != vec.end(); ++iter)
    {
        cout << *iter << ", ";
    }
    cout << endl;
    Solution solution;
    int result = solution.maxDistToClosest(vec);
    cout << result << endl;
}


