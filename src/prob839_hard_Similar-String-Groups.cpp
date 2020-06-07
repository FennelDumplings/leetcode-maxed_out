// prob839: Similar String Groups

/*
 * Two strings X and Y are similar if we can swap two letters (in different positions) of X, so that it equals Y. Also two strings X and Y are similar if they are equal.
 * For example, "tars" and "rats" are similar (swapping at positions 0 and 2), and "rats" and "arts" are similar, but "star" is not similar to "tars", "rats", or "arts".
 * Together, these form two connected groups by similarity: {"tars", "rats", "arts"} and {"star"}.  Notice that "tars" and "arts" are in the same group even though they are not similar.  Formally, each group is such that a word is in the group if and only if it is similar to at least one other word in the group.
 * We are given a list A of strings.  Every string in A is an anagram of every other string in A.  How many groups are there?
 */

/*
 * Example 1:
 * Input: A = ["tars","rats","arts","star"]
 * Output: 2
 */

/*
 * Constraints:
 * 1 <= A.length <= 2000
 * 1 <= A[i].length <= 1000
 * A.length * A[i].length <= 20000
 * All words in A consist of lowercase letters only.
 * All words in A have the same length and are anagrams of each other.
 * The judging time limit has been increased for this question.
 */

#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

class UnionFindSet
{
public:
    UnionFindSet(int n)
    {
        _rank = vector<int>(n, 0);
        _father = vector<int>(n, 0);
        for(int i = 1; i < n; ++i)
            _father[i] = i;
        set_num = n;
    }

    bool same(int x, int y)
    {
        return _find(x) == _find(y);
    }

    void merge(int a, int b)
    {
        int x = _find(a);
        int y = _find(b);

        if(x == y) return;

        if(_rank[x] > _rank[y])
            _father[y] = x;
        else
        {
            _father[x] = y;
            if(_rank[x] == _rank[y])
                ++_rank[y];
        }
        --set_num;
    }

    int stat()
    {
        return set_num;
    }

private:
    vector<int> _rank;
    vector<int> _father;
    int set_num;

    int _find(int x)
    {
        if(_father[x] == x)
            return x;
        return _father[x] = _find(_father[x]);
    }
};

class Solution {
public:
    int numSimilarGroups(vector<string>& A) {
        int n = A.size();
        UnionFindSet unionfindset(n);
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < n; ++j)
            {
                if(i == j) continue;
                if(_similar(A[i], A[j]))
                    unionfindset.merge(i, j);
            }
        return unionfindset.stat();
    }

private:
    bool _similar(const string& word1, const string& word2)
    {
        int n1 = word1.size(), n2 = word2.size();
        if(n1 != n2) return false;
        if(n1 == 1) return word1 == word2;
        int left = 0;
        while(left < n1 && word1[left] == word2[left])
            ++left;
        if(left == n1) return true;
        int right = left + 1;
        while(right < n1 && word1[right] == word2[right])
            ++right;
        if(right == n1) return false;
        if(word1[right] != word2[left] || word1[left] != word2[right])
            return false;
        int iter = right + 1;
        while(iter < n1)
        {
            if(word1[iter] != word2[iter])
                return false;
            ++iter;
        }
        return true;
    }
};
