// prob745: Prefix and Suffix Search

/*
 * Given many words, words[i] has weight i.
 * Design a class WordFilter that supports one function, WordFilter.f(String prefix, String suffix). It will return the word
 * with given prefix and suffix with maximum weight. If no word exists, return -1.
 */

/*
 * Examples:
 * Input:
 * WordFilter(["apple"])
 * WordFilter.f("a", "e") // returns 0
 * WordFilter.f("b", "") // returns -1
 */

/*
 * Note:
 * words has length in range [1, 15000].
 * For each test case, up to words.length queries WordFilter.f may be made.
 * words[i] has length in range [1, 10].
 * prefix, suffix have lengths in range [0, 10].
 * words[i] and prefix, suffix queries consist of lowercase letters only.
 */

#include <vector>
#include <string>
#include <map>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>

using namespace std;

const int ALPHABET = 26;

struct TrieNode
{
    vector<TrieNode*> children;
    set<int> word_ids;
    TrieNode()
    {
        children = vector<TrieNode*>(ALPHABET);
        word_ids = set<int>();
    }
};

class Trie
{
public:
    Trie()
    {
        root_prefix = new TrieNode();
        root_suffix = new TrieNode();
    }

    ~Trie()
    {
        if(root_prefix)
            _delete_sub_tree(root_prefix);
        if(root_suffix)
            _delete_sub_tree(root_suffix);
    }

    void insert_prefix(const string& s, int w)
    {
        TrieNode *iter = root_prefix;
        (iter -> word_ids).insert(w);
        for(const char &ch: s)
        {
            if(!(iter -> children)[ch - 'a'])
                (iter -> children)[ch - 'a'] = new TrieNode();
            iter = (iter -> children)[ch - 'a'];
            (iter -> word_ids).insert(w);
        }
    }

    void insert_suffix(const string& s, int w)
    {
        TrieNode *iter = root_suffix;
        (iter -> word_ids).insert(w);
        int n = s.size();
        for(int i = n - 1; i >= 0; --i)
        {
            const char &ch = s[i];
            if(!(iter -> children)[ch - 'a'])
                (iter -> children)[ch - 'a'] = new TrieNode();
            iter = (iter -> children)[ch - 'a'];
            (iter -> word_ids).insert(w);
        }
    }

    int search(const string& prefix, const string& suffix)
    {
        auto p1 = find(root_prefix, prefix);
        auto p2 = find(root_suffix, suffix);
        if(!p1 || !p2)
            return -1;
        set<int>& words_prefix = p1 -> word_ids;
        set<int>& words_suffix = p2 -> word_ids;
        auto it = words_prefix.rbegin();
        while(it != words_prefix.rend())
        {
            if(words_suffix.count(*it) > 0)
                return *it;
            ++it;
        }
        return -1;
    }

private:
    TrieNode *root_suffix;
    TrieNode *root_prefix;

    TrieNode* find(TrieNode* root, const string& prefix)
    {
        TrieNode *iter = root;
        for(const char &ch: prefix)
        {
            if(!(iter -> children)[ch - 'a'])
                return nullptr;
            iter = (iter -> children)[ch - 'a'];
        }
        return iter;
    }

    void _delete_sub_tree(TrieNode* node)
    {
        for(TrieNode *child: node -> children)
        {
            if(child)
                _delete_sub_tree(child);
        }
        delete node;
        node = nullptr;
    }
};

class WordFilter2 {
public:
    WordFilter2(vector<string>& words) {
        trie = new Trie();
        int n = words.size();
        for(int i = 0; i < n; ++i)
        {
            string w = words[i];
            trie -> insert_prefix(w, i);
            trie -> insert_suffix(w, i);
        }
    }

    int f(string prefix, string suffix) {
        reverse(suffix.begin(), suffix.end());
        return trie -> search(prefix, suffix);
    }

private:
    Trie *trie;
};

// 双向Trie

struct DoubleTrieNode
{
    bool prefix_terminate;
    bool suffix_terminate;
    unordered_map<string, DoubleTrieNode*> children;
    int max_idx;
    DoubleTrieNode()
    {
        prefix_terminate = false;
        suffix_terminate = false;
        children = unordered_map<string, DoubleTrieNode*>();
        max_idx = -1;
    }
};

class DoubleTrie
{
public:
    DoubleTrie()
    {
        root = new DoubleTrieNode();
    }

    ~DoubleTrie()
    {
        _delete_sub_tree(root);
    }

    void insert(const string& s, int w)
    {
        int n = s.size();
        _insert(root, s, 0, n - 1, w);
    }

    int search(const string& prefix, const string& suffix)
    {
       auto it = _find(prefix, suffix);
        if(!it)
            return -1;
        return it -> max_idx;
    }

private:
    DoubleTrieNode *root;

    void _delete_sub_tree(DoubleTrieNode* node)
    {
        for(auto child: node -> children)
            if(child.second)
                _delete_sub_tree(child.second);
        delete node;
        node = nullptr;
    }

    DoubleTrieNode* _find(const string& prefix, const string& suffix)
    {
        int np = prefix.size();
        int ns = suffix.size();
        int i = 0, j = ns - 1;
        DoubleTrieNode *iter = root;
        while(i < np && j >= 0)
        {
            string nxt_char_set = string(1, prefix[i]) + suffix[j];
            DoubleTrieNode *&nxt = (iter -> children)[nxt_char_set];
            if(!nxt)
                return nullptr;
            iter = nxt;
            ++i;
            --j;
        }
        while(i < np)
        {
            string nxt_char_set = string(1, prefix[i]) + '#';
            DoubleTrieNode *&nxt = (iter -> children)[nxt_char_set];
            if(!nxt)
                return nullptr;
            iter = nxt;
            ++i;
        }
        while(j >= 0)
        {
            string nxt_char_set = '#' + string(1, suffix[j]);
            DoubleTrieNode *&nxt = (iter -> children)[nxt_char_set];
            if(!nxt)
                return nullptr;
            iter = nxt;
            --j;
        }
        return iter;
    }

    void _insert(DoubleTrieNode* node, const string& s, int i, int j, const int w)
    {
        node -> max_idx = max(node -> max_idx, w);
        int n = s.size();
        if(!node -> prefix_terminate && !node -> suffix_terminate)
        {
            if(i <= n - 1 && j >= 0)
            {
                string nxt_char_set = string(1, s[i]) + s[j];
                DoubleTrieNode *&nxt = (node -> children)[nxt_char_set];
                if(!nxt)
                    nxt = new DoubleTrieNode();
                _insert(nxt, s, i + 1, j - 1, w);
            }
        }
        if(i <= n - 1 && !node -> prefix_terminate)
        {
            string nxt_char_set = string(1, s[i]) + '#';
            DoubleTrieNode *&nxt = (node -> children)[nxt_char_set];
            if(!nxt)
                nxt = new DoubleTrieNode();
            nxt -> suffix_terminate = true;
            _insert(nxt, s, i + 1, j, w);
        }
        if(j >= 0 && !node -> suffix_terminate)
        {
            string nxt_char_set = '#' + string(1, s[j]);
            DoubleTrieNode *&nxt = (node -> children)[nxt_char_set];
            if(!nxt)
                nxt = new DoubleTrieNode();
            nxt -> prefix_terminate = true;
            _insert(nxt, s, i, j - 1, w);
        }
    }
};


class WordFilter {
public:
    WordFilter(vector<string>& words) {
        trie = new DoubleTrie();
        int n = words.size();
        for(int i = 0; i < n; ++i)
        {
            string w = words[i];
            trie -> insert(w, i);
        }
    }

    int f(string prefix, string suffix) {
        return trie -> search(prefix, suffix);
    }

private:
    DoubleTrie *trie;
};


["WordFilter","f","f","f","f","f","f","f","f","f","f"]
[[["cabaabaaaa","ccbcababac","bacaabccba","bcbbcbacaa","abcaccbcaa","accabaccaa","cabcbbbcca","ababccabcb","caccbbcbab","bccbacbcba"]],["bccbacbcba","a"],["ab","abcaccbcaa"],["a","aa"],["cabaaba","abaaaa"],["cacc","accbbcbab"],["ccbcab","bac"],["bac","cba"],["ac","accabaccaa"],["bcbb","aa"],["ccbca","cbcababac"]]

["WordFilter","f"]
[[["bccbacbcba"]],["bccbacbcba","a"]]
