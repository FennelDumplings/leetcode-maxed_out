// prob737: Sentence Similarity II

/*
 * Given two sentences words1, words2 (each represented as an array of strings), and a list of similar word pairs pairs, determine if two sentences are similar.
 * For example, words1 = ["great", "acting", "skills"] and words2 = ["fine", "drama", "talent"] are similar, if the similar word pairs are pairs = [["great", "good"], ["fine", "good"], ["acting","drama"], ["skills","talent"]].
 * Note that the similarity relation is transitive. For example, if "great" and "good" are similar, and "fine" and "good" are similar, then "great" and "fine" are similar.
 * Similarity is also symmetric. For example, "great" and "fine" being similar is the same as "fine" and "great" being similar.
 * Also, a word is always similar with itself. For example, the sentences words1 = ["great"], words2 = ["great"], pairs = [] are similar, even though there are no specified similar word pairs.
 * Finally, sentences can only be similar if they have the same number of words. So a sentence like words1 = ["great"] can never be similar to words2 = ["doubleplus","good"].
 */

/*
 * Note:
 * The length of words1 and words2 will not exceed 1000.
 * The length of pairs will not exceed 2000.
 * The length of each pairs[i] will be 2.
 * The length of each words[i] and pairs[i][j] will be in the range [1, 20].
 */

#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class UniFindSet
{
public:
    UniFindSet(int n)
    {
        // 1 ~ n 共 n 个点
        _father = vector<int>(n + 1, -1);
        _rank = vector<int>(n + 1, 0);
        for(int i = 1; i <= n; ++i)
            _father[i] = i;
    }

    bool same(int a, int b)
    {
        return _find(a) == _find(b);
    }

    void merge(int a, int b)
    {
        int x = _find(a);
        int y = _find(b);
        if(x == y)
            return;

        if(_rank[x] > _rank[y])
            _father[y] = x;
        else
        {
            _father[x] = y;
            if(_rank[x] == _rank[y])
                ++_rank[y];
        }
    }

private:
    vector<int> _father;
    vector<int> _rank;

    int _find(int x)
    {
        if(_father[x] == x)
            return x;
        return _father[x] = _find(_father[x]);
    }
};

class Solution {
public:
    bool areSentencesSimilarTwo(vector<string>& words1, vector<string>& words2, vector<vector<string>>& pairs) {
        unordered_map<string, int> id;
        unordered_map<int, unordered_set<int> > mapping;
        int cur_id = 1;
        for(const vector<string>& pair: pairs)
        {
            if(id[pair[0]] == 0)
            {
                id[pair[0]] = cur_id;
                ++cur_id;
            }
            if(id[pair[1]] == 0)
            {
                id[pair[1]] = cur_id;
                ++cur_id;
            }
        }
        for(const string& word: words1)
            if(id[word] == 0)
            {
                id[word] = cur_id;
                ++cur_id;
            }
        for(const string& word: words2)
            if(id[word] == 0)
            {
                id[word] = cur_id;
                ++cur_id;
            }
        UniFindSet unifindset(cur_id - 1);

        for(const vector<string>& pair: pairs)
            unifindset.merge(id[pair[0]], id[pair[1]]);
        if(words1.size() != words2.size())
            return false;
        for(int i = 0; i < (int)words1.size(); ++i)
        {
            string &word1 = words1[i], &word2 = words2[i];
            if(word1 != word2 && !unifindset.same(id[word1], id[word2]))
                return false;
        }
        return true;
    }
};
