#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    bool areSentencesSimilar(string sentence1, string sentence2) {
        vector<string> words1, words2;
        get_word(sentence1, words1);
        get_word(sentence2, words2);
        return check(words1, words2);
    }

private:
    bool check(const vector<string>& words1, const vector<string>& words2)
    {
        int n1 = words1.size(), n2 = words2.size();
        if(n1 > n2)
            return check(words2, words1);
        int l = 0;
        while(l < n1 && words1[l] == words2[l])
            ++l;
        int r1 = n1 - 1, r2 = n2 - 1;
        while(r1 >= l && words1[r1] == words2[r2])
        {
            --r1;
            --r2;
        }
        return r1 < l;
    }

    void get_word(const string& sentence, vector<string>& words)
    {
        int n = sentence.size();
        int i = 0;
        while(i < n)
        {
            int j = i;
            while(j < n && sentence[j] == ' ')
                ++j;
            if(j == n)
                break;
            i = j;
            while(j < n && sentence[j] != ' ')
                ++j;
            words.emplace_back(sentence.substr(i, j - i));
            i = j;
        }
    }
};
