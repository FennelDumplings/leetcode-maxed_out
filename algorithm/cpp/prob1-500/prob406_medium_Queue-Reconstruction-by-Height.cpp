// prob406: Queue Reconstruction by Height

/*
 * Suppose you have a random list of people standing in a queue. Each person is described by a pair of integers (h, k),
 * where h is the height of the person and k is the number of people in front of this person who have a height greater
 * than or equal to h. Write an algorithm to reconstruct the queue.
 */

/*
 * Note:
 * The number of people is less than 1,100.
 */

/*
 * Example
 * Input:
 * [[7,0], [4,4], [7,1], [5,0], [6,1], [5,2]]
 * Output:
 * [[5,0], [7,0], [5,2], [6,1], [4,4], [7,1]]
 */

#include <vector>
#include <algorithm>
#include <list>

using namespace std;

class Solution {
public:
    vector<vector<int>> reconstructQueue(vector<vector<int>>& people) {
        if(people.empty()) return vector<vector<int> >();
        int n = people.size();
        sort(people.begin(), people.end(), Cmp());
        vector<vector<int> > result;
        for(int i = 0; i < n; ++i)
            result.insert(result.begin() + people[i][1], people[i]);
        return result;
    }

private:
    struct Cmp
    {
        bool operator()(const vector<int>& vec1, const vector<int>& vec2)
        {
            if(vec1[0] == vec2[0])
                return vec1[1] < vec2[1];
            return vec1[0] > vec2[0];
        }
    };
};
