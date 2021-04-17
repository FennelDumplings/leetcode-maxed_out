// prob966: Vowel Spellchecker

/*
 * https://leetcode-cn.com/problems/vowel-spellchecker/
 */

#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

class Solution {
public:
    vector<string> spellchecker(vector<string>& wordlist, vector<string>& queries) {
        unordered_set<string> setting;
        unordered_map<string, string> mapping;
        unordered_map<string, string> mapping2;
        for(const string& word: wordlist)
        {
            setting.insert(word);
            string key = process(word);
            string key2 = process2(word);
            if(mapping2.count(key2) == 0)
                mapping2[key2] = word;
            if(mapping.count(key) == 0)
                mapping[key] = word;
        }
        vector<string> result;
        for(const string& q: queries)
        {
            if(setting.count(q) > 0)
                result.push_back(q);
            else
            {
                string key2 = process2(q);
                string key = process(q);
                if(mapping2.count(key2) > 0)
                    result.push_back(mapping2[key2]);
                else if(mapping.count(key) > 0)
                    result.push_back(mapping[key]);
                else
                    result.push_back("");
            }
        }
        return result;
    }

private:
    const string vowels = "aeiouAEIOU";

    string process2(const string& s)
    {
        string result = s;
        for(char &ch: result)
            if(ch >= 'A' && ch <= 'Z')
                ch += 'a' - 'A';
        return result;
    }

    string process(const string& s)
    {
        string result = s;
        for(char &ch: result)
            if(ch >= 'A' && ch <= 'Z')
                ch += 'a' - 'A';
        for(char &ch: result)
            if(ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u')
                ch = 'a';
        return result;
    }
};


//---------------------------------------------------------------

const string vowels = "aeiouAEIOU";

bool check(const char& c1, const char& c2)
{
    if(c1 == c2)
        return true;
    if(abs(c1 - c2) == 'a' - 'A')
        return true;
    if(vowels.find(c1) != vowels.npos && vowels.find(c2) != vowels.npos)
        return true;
    return false;
}

class MyCmp
{
public:
    bool operator()(const string& s1, const string& s2) const
    {
        int n1 = s1.size(), n2 = s2.size();
        if(n1 != n2)
            return false;
        int i = 0;
        while(i < n1)
        {
            if(!check(s1[i], s2[i]))
                return false;
            ++i;
        }
        return true;
    }
};

class MyHash
{
public:
    int operator()(const string& s) const
    {
        return (int)s.size();
    }
};

class Solution_2 {
public:
    vector<string> spellchecker(vector<string>& wordlist, vector<string>& queries) {
        unordered_map<string, unordered_set<string>, MyHash, MyCmp> words;
        for(const string& word: wordlist)
        {
            auto it = words.find(word);
            if(it != words.end())
                (it -> second).insert(word);
            else
                words[word].insert(word);
        }
        vector<string> result;
        for(const string& q: queries)
        {
            if(words.count(q) == 0)
                result.push_back("");
            else if(words[q].count(q) > 0)
                result.push_back(q);
            else
                result.push_back(words.find(q) -> first);
        }
        return result;
    }
};
