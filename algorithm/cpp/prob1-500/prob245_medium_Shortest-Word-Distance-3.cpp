// prob245: Shortest Word Distance III

/*
 * Given a list of words and two words word1 and word2, return the shortest distance between these two words in the list.
 * word1 and word2 may be the same and they represent two individual words in the list.
 */

/*
 * Example:
 * Assume that words = ["practice", "makes", "perfect", "coding", "makes"].
 * Input: word1 = “makes”, word2 = “coding”
 * Output: 1
 * Input: word1 = "makes", word2 = "makes"
 * Output: 3
 */

/*
 * Note:
 * You may assume word1 and word2 are both in the list.
 */

#include <vector>
#include <string>

using namespace std;


class Solution_243 {
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


class Solution {
public:
    int shortestWordDistance(vector<string>& words, string word1, string word2) {
        if(word1 != word2)
        {
            Solution_243 solution_243;
            return solution_243.shortestDistance(words, word1, word2);
        }
        else
        {
            int n = words.size();
            int i1 = -1, i2 = -1;
            int result = n;
            int flag = 1;
            for(int i = 0; i < n; ++i)
            {
                if(words[i] == word1)
                {
                    if(flag)
                    {
                        i1 = i;
                        if(i2 != -1)
                            result = min(result, i1 - i2);
                        flag ^= 1;
                    }
                    else
                    {
                        i2 = i;
                        if(i1 != -1)
                            result = min(result, i2 - i1);
                        flag ^= 1;
                    }
                }
            }
            return result;
        }
    }
};


