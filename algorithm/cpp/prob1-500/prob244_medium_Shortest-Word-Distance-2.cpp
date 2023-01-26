// prob244: Shortest Word Distance II

/*
 * Design a class which receives a list of words in the constructor, and implements a method that takes two
 * words word1 and word2 and return the shortest distance between these two words in the list. Your method
 * will be called repeatedly many times with different parameters. 
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

class WordDistance {
public:
    WordDistance(vector<string>& words) {
        n = words.size();
        for(int i = 0; i < n; ++i)
            mapping[words[i]].insert(i);
    }

    int shortest(string word1, string word2) {
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

private:
    using PSSI = pair<string, set<int>>;
    unordered_map<string, set<int>> mapping; // word -> idx 集合
    int n;
};

/**
 * Your WordDistance object will be instantiated and called as such:
 * WordDistance* obj = new WordDistance(words);
 * int param_1 = obj->shortest(word1,word2);
 */
