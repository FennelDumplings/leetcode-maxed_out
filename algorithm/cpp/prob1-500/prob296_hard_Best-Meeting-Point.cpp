// prob296: Best Meeting Point

/*
 * A group of two or more people wants to meet and minimize the total travel distance. You are given a 2D grid of values 0 or 1, where each 1 marks the home of someone in the group. The distance is calculated using Manhattan Distance, where distance(p1, p2) = |p2.x - p1.x| + |p2.y - p1.y|.
 */

/*
 * Example:
 *
 * Input:
 *
 * 1 - 0 - 0 - 0 - 1
 * |   |   |   |   |
 * 0 - 0 - 0 - 0 - 0
 * |   |   |   |   |
 * 0 - 0 - 1 - 0 - 0
 *
 * Output: 6
 *
 * Explanation: Given three people living at (0,0), (0,4), and (2,2):
 *              The point (0,2) is an ideal meeting point, as the total travel distance
 *              of 2+2+2=6 is minimal. So return 6.
 *
 */

#include <vector>
#include <climits>
#include <cmath>
#include <algorithm>

using namespace std;

class Solution {
public:
    int minTotalDistance(vector<vector<int>>& grid) {
        if(grid.empty()) return 0;
        int n = grid.size(), m = grid[0].size();
        vector<int> xs, ys;
        vector<PII> persons;
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < m; ++j)
            {
                if(grid[i][j] == 1)
                {
                    xs.push_back(i);
                    ys.push_back(j);
                    persons.push_back(PII(i, j));
                }
            }
        int nx = xs.size();
        int ny = ys.size();
        nth_element(xs.begin(), xs.begin() + nx / 2, xs.end());
        int mid_x = *(xs.begin() + nx / 2);
        nth_element(ys.begin(), ys.begin() + ny / 2, ys.end());
        int mid_y = *(ys.begin() + ny / 2);
        int result = 0;
        for(PII person: persons)
            result += manhattan(person, mid_x, mid_y);
        return result;
    }

private:
    using PII = pair<int, int>;

    int manhattan(const PII& person, int i, int j)
    {
        return abs(person.first - i) + abs(person.second - j);
    }
};

// TLE
class Solution_2 {
public:
    int minTotalDistance(vector<vector<int>>& grid) {
        if(grid.empty()) return 0;
        int n = grid.size(), m = grid[0].size();
        vector<PII> persons;
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < m; ++j)
            {
                if(grid[i][j] == 1)
                    persons.push_back(PII(i, j));
            }
        int result = INT_MAX;
        for(int i = 0; i < n; ++i)
        {
            for(int j = 0; j < m; ++j)
            {
                int dist = 0;
                for(PII person: persons)
                    dist += manhattan(person, i, j);
                result = min(result, dist);
            }
        }
        return result;
    }

private:
    using PII = pair<int, int>;

    int manhattan(const PII& person, int i, int j)
    {
        return abs(person.first - i) + abs(person.second - j);
    }
};
