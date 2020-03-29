// prob288: Unique Word Abbreviation

/*
 * An abbreviation of a word follows the form <first letter><number><last letter>. Below are some examples of word abbreviations:
 * a) it                      --> it    (no abbreviation)
 *      1
 *      ↓
 * b) d|o|g                   --> d1g
 *
 *               1    1  1
 *      1---5----0----5--8
 *      ↓   ↓    ↓    ↓  ↓
 * c) i|nternationalizatio|n  --> i18n
 *
 *               1
 *      1---5----0
 *      ↓   ↓    ↓
 * d) l|ocalizatio|n          --> l10n
 */

/*
 * Assume you have a dictionary and given a word, find whether its abbreviation is unique in the dictionary.
 * A word's abbreviation is unique if no other word from the dictionary has the same abbreviation.
 */

/*
 * Example:
 * Given dictionary = [ "deer", "door", "cake", "card"  ]
 * isUnique("dear") -> false
 * isUnique("cart") -> true
 * isUnique("cane") -> false
 * isUnique("make") -> true
 */

#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

class ValidWordAbbr {
public:
    ValidWordAbbr(vector<string>& dictionary) {
        mapping = unordered_map<string, vector<string> >();
        for(const string &word: dictionary)
        {
            string key = _get_key(word);
            auto it = mapping.find(key);
            if(it != mapping.end())
                mapping[key].push_back(word);
            else
                mapping[key] = vector<string>({word});
        }
    }

    bool isUnique(string word) {
        string key = _get_key(word);
        auto it = mapping.find(key);
        if(it == mapping.end()) return true;
        for(const string& w: mapping[key])
            if(w != word)
                return false;
        return true;
    }

private:
    unordered_map<string, vector<string> > mapping;

    string _get_key(const string& word)
    {
        int n = word.size();
        if(n <= 2) return word;
        string result(1, word[0]);
        result += to_string(n - 2);
        result += word[n - 1];
        return result;
    }
};
