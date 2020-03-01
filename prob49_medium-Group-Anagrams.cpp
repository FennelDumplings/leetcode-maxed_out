// prob49: Group Anagrams

/*
 * Given an array of strings, group anagrams together.
 */

/*
 * Note:
 * All inputs will be in lowercase.
 * The order of your output does not matter.
 */

/*
 * Example:
 * Input: ["eat", "tea", "tan", "ate", "nat", "bat"],
 * Output:
 * [
 *   ["ate","eat","tea"],
 *   ["nat","tan"],
 *   ["bat"]
 * ]
 */

#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>

using namespace std;

// 用字符计数做键
// #..#..#..
// #..# 夹着的是对应位置字母的个数
// 时间虽然 O(NK) 但是常数大(26) 一般跑不过 O(NKlogK)
class Solution_optim2 {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        if(strs.empty()) return vector<vector<string> >();
        vector<vector<string> > results;
        unordered_map<string, int> mapping; // string -> 索引
        int key_num = 0;
        for(string word: strs)
        {
            string tmp = _count(word);
            auto it = mapping.find(tmp);
            if(it != mapping.end())
                results[mapping[tmp]].push_back(word);
            else
            {
                mapping[tmp] = key_num++;
                results.push_back(vector<string>());
                results[mapping[tmp]].push_back(word);
            }
        }
        return results;
    }

private:
    string _count(const string& word)
    {
        vector<int> counting(26, 0);
        string result = "#";
        for(char c: word)
        {
            int index = c - 'a';
            counting[index]++;
        }
        for(int i = 0; i < 26; ++i)
            result += to_string(counting[i]) + "#";
        return result;
    }
};

// 排序后的串相同才是字母异位词
class Solution_optim1 {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        if(strs.empty()) return vector<vector<string> >();
        vector<vector<string> > results;
        unordered_map<string, int> mapping; // string -> 索引
        int key_num = 0;
        for(string word: strs)
        {
            string tmp = word;
            sort(tmp.begin(), tmp.end());
            auto it = mapping.find(tmp);
            if(it != mapping.end())
                results[mapping[tmp]].push_back(word);
            else
            {
                mapping[tmp] = key_num++;
                results.push_back(vector<string>());
                results[mapping[tmp]].push_back(word);
            }
        }
        return results;
    }
};

// 排序的另一种写法
class Solution_optim2 {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string, vector<string>> dict;
        for (auto &str : strs)
        {
            string key = str;
            sort(key.begin(), key.end());
            dict[key].push_back(move(str));
        }

        vector<vector<string>> res;
        for (auto i = dict.begin(); i != dict.end(); i ++ )
        {
            res.push_back(move(i -> second));
        }

        return res;
    }
};

// TLE
class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        if(strs.empty()) return vector<vector<string> >();
        vector<vector<string> > results;
        vector<unordered_map<char, int> > mappings;
        for(string word: strs)
        {
            int index = _in_mapping(mappings, word);
            if(index == -1)
            {
                mappings.push_back(unordered_map<char, int>());
                for(char c: word)
                {
                    if(mappings[mappings.size() - 1].count(c) != 0)
                        ++mappings[mappings.size() - 1][c];
                    else
                        mappings[mappings.size() - 1][c] = 1;
                }
                results.push_back(vector<string>());
                results[results.size() - 1].push_back(word);
            }
            else
                results[index].push_back(word);
        }
        return results;
    }

private:
    int _in_mapping(const vector<unordered_map<char, int> >& mappings, const string& word)
    {
        int n = mappings.size();
        unordered_map<char, int> tmp_mapping;
        for(char c: word)
        {
            if(tmp_mapping.count(c) != 0)
                ++tmp_mapping[c];
            else
                tmp_mapping[c] = 1;
        }
        for(int i = 0; i < n; ++i)
            if(_is_eq_mapping(mappings[i], tmp_mapping))
                return i;
        return -1;
    }

    bool _is_eq_mapping(const unordered_map<char, int>& mapping1, const unordered_map<char, int>& mapping2)
    {
        if(mapping1.empty() && mapping2.empty()) return true;
        if(mapping1.empty() || mapping2.empty()) return false;
        for(auto it = mapping1.begin(); it != mapping1.end(); it++)
            if(mapping2.find(it -> first) == mapping2.end())
                return false;
        for(auto it = mapping2.begin(); it != mapping2.end(); it++)
        {
            char c = it -> first;
            auto iter = mapping1.find(c);
            if(iter == mapping1.end())
                return false;
            int count = it -> second;
            if(iter -> second != count)
                return false;
        }
        return true;
    }
};
