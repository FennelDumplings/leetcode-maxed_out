// interview16.02: 单词频率

/*
 * https://leetcode-cn.com/problems/words-frequency-lcci/
 */

#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

class WordsFrequency {
public:
    WordsFrequency(vector<string>& book) {
        for(const string &word: book)
            ++mapping[word];
    }

    int get(string word) {
        return mapping[word];
    }

private:
    unordered_map<string, int> mapping;
};
