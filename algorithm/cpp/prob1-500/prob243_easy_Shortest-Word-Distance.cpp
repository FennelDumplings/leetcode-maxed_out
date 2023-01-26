// prob243: Shortest Word Distance

/*
 * Given a list of words and two words word1 and word2, return the shortest distance between these two words in the list.
 */

/*
 * Example:
 * Assume that words = ["practice", "makes", "perfect", "coding", "makes"].
 * Input: word1 = “coding”, word2 = “practice”
 * Output: 3
 * Input: word1 = "makes", word2 = "coding"
 * Output: 1
 */

/*
 * Note:
 * You may assume that word1 does not equal to word2, and word1 and word2 are both in the list.
 */

#include <vector>
#include <string>
#include <unordered_map>
#include <set>

using namespace std;

class Solution {
public:
    int shortestDistance(vector<string>& words, string word1, string word2) {
        using PSSI = pair<string, set<int>>;
        unordered_map<string, set<int>> mapping; // word -> idx 集合
        int n = words.size();
        for(int i = 0; i < n; ++i)
        {
            mapping[words[i]].insert(i);
        }
        int result = n;
        for(int idx1: mapping[word1])
        {
            auto idx2_iter = mapping[word2].lower_bound(idx1);
            if(idx2_iter != mapping[word2].end())
            {
                int idx2 = *idx2_iter;
                result = min(result, idx2 - idx1);
            }
            if(idx2_iter != mapping[word2].begin())
            {
                --idx2_iter;
                int idx2 = *idx2_iter;
                result = min(result, idx1 - idx2);
            }
        }
        return result;
    }
};


class Solution_2 {
public:
    int shortestDistance(vector<string>& words, string word1, string word2) {
        int n = words.size();
        int i1 = -1, i2 = -1;
        int result = n;
        for(int i = 0; i < n; ++i)
        {
            if(words[i] == word1)
            {
                i1 = i;
                if(i2 != -1)
                    result = min(result, i1 - i2);
            }
            if(words[i] == word2)
            {
                i2 = i;
                if(i1 != -1)
                    result = min(result, i2 - i1);
            }
        }
        return result;
    }
};
