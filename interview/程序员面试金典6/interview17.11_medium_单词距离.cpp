// interview17.11: 单词距离

/*
 * https://leetcode-cn.com/problems/find-closest-lcci/
 */

#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    int findClosest(vector<string>& words, string word1, string word2) {
        int n = words.size();
        unordered_map<string, vector<int>> mapping;
        for(int i = 0; i < n; ++i)
            mapping[words[i]].push_back(i);
        if(mapping.count(word1) == 0 || mapping.count(word2) == 0)
            return n;
        vector<int> &idxs1 = mapping[word1];
        vector<int> &idxs2 = mapping[word2];
        int n1 = idxs1.size();
        int n2 = idxs2.size();
        int iter1 = 0, iter2 = 0;
        int result = n;
        while(iter1 < n1 && iter2 < n2)
        {
            if(idxs2[iter2] > idxs1[iter1])
            {
                result = min(result, idxs2[iter2] - idxs1[iter1]);
                ++iter1;
            }
            else
            {
                result = min(result, idxs1[iter1] - idxs2[iter2]);
                ++iter2;
            }
        }
        return result;
    }
};
