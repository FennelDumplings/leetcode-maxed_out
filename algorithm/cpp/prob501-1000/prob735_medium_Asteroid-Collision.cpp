// prob735: Asteroid Collision

/*
 * We are given an array asteroids of integers representing asteroids in a row.
 *
 * For each asteroid, the absolute value represents its size, and the sign represents its direction (positive meaning right, negative meaning left). Each asteroid moves at the same speed.
 *
 * Find out the state of the asteroids after all collisions. If two asteroids meet, the smaller one will explode. If both are the same size, both will explode. Two asteroids moving in the same direction will never meet.
 */

/*
 * Example 1:
 * Input:
 * asteroids = [5, 10, -5]
 * Output: [5, 10]
 * Explanation:
 * The 10 and -5 collide resulting in 10.  The 5 and 10 never collide.
 * Example 2:
 * Input:
 * asteroids = [8, -8]
 * Output: []
 * Explanation:
 * The 8 and -8 collide exploding each other.
 * Example 3:
 * Input:
 * asteroids = [10, 2, -5]
 * Output: [10]
 * Explanation:
 * The 2 and -5 collide resulting in -5.  The 10 and -5 collide resulting in 10.
 * Example 4:
 * Input:
 * asteroids = [-2, -1, 1, 2]
 * Output: [-2, -1, 1, 2]
 * Explanation:
 * The -2 and -1 are moving left, while the 1 and 2 are moving right.
 * Asteroids moving the same direction never meet, so no asteroids will meet each other.
 */

/*
 * Note:
 *
 * The length of asteroids will be at most 10000.
 * Each asteroid will be a non-zero integer in the range [-1000, 1000]..
 */

#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<int> asteroidCollision(vector<int>& asteroids) {
        int n = asteroids.size();
        if(n <= 1) return asteroids;
        // + 进栈
        // - 弹栈
        stack<int> st;
        vector<int> result;
        for(int i = 0; i < n; ++i)
        {
            int a = asteroids[i];
            if(a > 0)
            {
                st.push(i);
            }
            else if(a < 0)
            {
                while(!st.empty() && asteroids[st.top()] < -a)
                    st.pop();
                if(st.empty())
                    result.push_back(i);
                else if(asteroids[st.top()] == -a)
                    st.pop();
            }
            else
                result.push_back(i);
        }
        while(!st.empty())
        {
            result.push_back(st.top());
            st.pop();
        }
        sort(result.begin(), result.end());
        for(int &i: result) i = asteroids[i];
        return result;
    }
};
