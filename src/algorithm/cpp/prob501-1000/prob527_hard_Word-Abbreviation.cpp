// prbo527: Word Abbreviation

/*
 * https://leetcode-cn.com/problems/word-abbreviation/
 */

#include <vector>
#include <string>
#include <sstream>
#include <unordered_map>
#include <map>

using namespace std;

struct MyKey
{
    int operator()(const string& s) const
    {
        int hash = s.size();
        int r = s[hash - 1] - 'a';
        hash *= 100;
        hash += r;
        int l = s[0] - 'a';
        hash *= 100;
        hash += l;
        return hash;
    }
};

const int ALPHABETS = 26;

struct TrieNode
{
    vector<TrieNode*> children;
    int words_cnt; // 具有该节点表示的前缀的字符串的个数
    TrieNode()
    {
        children = vector<TrieNode*>(ALPHABETS, nullptr);
        words_cnt = 0;
    }
    ~TrieNode(){}
};

class Trie
{
public:
    /** Initialize your data structure here. */
    Trie()
    {
        root = new TrieNode();
    }

    ~Trie()
    {
        delete_sub_tree(root);
    }

    void insert(const string& word)
    {
        TrieNode *iter = root;
        for(const char c: word)
        {
            if(!(iter -> children[_to_int(c)]))
                (iter -> children)[_to_int(c)] = new TrieNode();
            iter = (iter -> children)[_to_int(c)];
            ++(iter -> words_cnt);
        }
    }

    int query(const string& s)
    {
        int deep = find(s);
        return deep;
    }

private:
    TrieNode *root;

    void delete_sub_tree(TrieNode *node)
    {
        for(TrieNode *child: node -> children)
            if(child)
                delete_sub_tree(child);
        delete node;
        node = nullptr;
    }

    int _to_int(char ch) const
    {
        return ch - 'a';
    }

    int find(const string& word) const
    {
        int deep = 0;
        const TrieNode* iter = root;
        for(const char c: word)
        {
            if(iter -> words_cnt == 1)
                return deep;
            iter = (iter -> children)[_to_int(c)];
            if(iter == nullptr)
                break;
            ++deep;
        }
        return -1;
    }
};

class Solution {
public:
    vector<string> wordsAbbreviation(vector<string>& dict) {
        MyKey my_key;
        unordered_map<int, Trie*> bucket;
        for(const string& w: dict)
        {
            int key = my_key(w);
            if(bucket.count(key) == 0)
                bucket[key] = new Trie();
            bucket[key] -> insert(w);
        }
        int n = dict.size();
        vector<string> result(n);
        for(int i = 0; i < n; ++i)
        {
            const string &w = dict[i];
            int k = my_key(w);
            int prefix_len = bucket[k] -> query(w);
            int len = w.size();
            if(len - 1 - prefix_len >= 2)
                result[i] = w.substr(0, prefix_len) + to_string(len - 1 - prefix_len) + w[len - 1];
            else
                result[i] = w;
        }
        return result;
    }
};

// ---

class Solution_2 {
public:
    vector<string> wordsAbbreviation(vector<string>& dict) {
        MyKey my_key;
        unordered_map<int, map<string, string>> bucket;
        for(const string& w: dict)
        {
            int key = my_key(w);
            bucket[key][w] = w;
        }
        for(auto &b: bucket)
        {
            adjust(b.second);
        }
        int n = dict.size();
        vector<string> result(n);
        for(int i = 0; i < n; ++i)
        {
            int k = my_key(dict[i]);
            result[i] = bucket[k][dict[i]];
        }
        return result;
    }

private:
    void adjust(map<string, string>& words)
    {
        int len = (words.begin() -> first).size();
        if(len <= 3) return;
        auto it = words.begin();
        int prev_prefix_len = 1;
        while(it != words.end())
        {
            const string &w = (it -> first);
            int prefix_len = prev_prefix_len;
            ++it;
            if(it != words.end())
            {
                prev_prefix_len = common_prefix_len(w, it -> first);
                prefix_len = max(prefix_len, prev_prefix_len);
            }
            --it;
            if(len - 1 - prefix_len >= 2)
                it -> second = w.substr(0, prefix_len) + to_string(len - 1 - prefix_len) + w[len - 1];
            ++it;
        }
    }

    int common_prefix_len(const string& a, const string& b)
    {
        int na = a.size(), nb = b.size();
        int i = 0;
        while(i < na && i < nb && a[i] == b[i])
            ++i;
        return i + 1;
    }
};


