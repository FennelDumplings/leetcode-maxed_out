// prob354: Russian Doll Envelopes

/*
 * You have a number of envelopes with widths and heights given as a pair of integers (w, h).
 * One envelope can fit into another if and only if both the width and height of one envelope is greater than
 * the width and height of the other envelope.
 * What is the maximum number of envelopes can you Russian doll? (put one inside other)
 * Note:
 * Rotation is not allowed.
 */

/*
 * Example:
 * Input: [[5,4],[6,4],[6,7],[2,3]]
 * Output: 3
 * Explanation: The maximum number of envelopes you can Russian doll is 3 ([2,3] => [5,4] => [6,7]).
 */

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int maxEnvelopes(vector<vector<int>>& envelopes) {
        if(envelopes.empty()) return 0;
        int n = envelopes.size();
        sort(envelopes.begin(), envelopes.end(), cmp);
        vector<int> vec;
        for(int i = 0; i < n; ++i)
        {
            int idx = lower_bound(vec.begin(), vec.end(), envelopes[i][1]) - vec.begin();
            if(idx < (int)vec.size())
                vec[idx] = envelopes[i][1];
            else
                vec.push_back(envelopes[i][1]);
        }
        return vec.size();
    }

private:
    static bool cmp(const vector<int>& vec1, const vector<int>& vec2)
    {
        if(vec1[0] == vec2[0])
            return vec1[1] > vec2[1];
        return vec1[0] < vec2[0];
    }
};
