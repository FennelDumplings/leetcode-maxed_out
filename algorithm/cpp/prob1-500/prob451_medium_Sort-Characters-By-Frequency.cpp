// prob451: Sort Characters By Frequency

/*
 * Given a string, sort it in decreasing order based on the frequency of characters.
 */

#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
public:
    string frequencySort(string s) {
        int n = s.size();
        if(n <= 2) return s;
        unordered_map<char, int> char_cnt;
        for(char c: s)
            ++char_cnt[c];
        vector<vector<char> > buckets(n + 1, vector<char>());
        for(auto it = char_cnt.begin(); it != char_cnt.end(); ++it)
            buckets[it -> second].push_back(it -> first);
        string result;
        for(int i = n; i >= 1; --i)
            if(!buckets[i].empty())
            {
                for(char c: buckets[i])
                {
                    string item(i, c);
                    result.insert(result.end(), item.begin(), item.end());
                }
            }
        return result;
    }
};
