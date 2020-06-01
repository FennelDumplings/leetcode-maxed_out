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

using namespace std;

const int ALPHABETS = 26;

struct TrieNode
{
    int w;
    vector<TrieNode*> children;
    TrieNode()
    {
        w = -1;
        children = vector<TrieNode*>(ALPHABETS, nullptr);
    }
    ~TrieNode()
    {
        for(TrieNode *child: children)
        {
            if(child)
            {
                delete child;
                child = nullptr;
            }
        }
    }
};

class TriePrefix
{
public:
    TriePrefix()
    {
        root = new TrieNode();
    }

    ~TriePrefix()
    {
        if(root)
        {
            delete root;
            root = nullptr;
        }
    }

    void insert(const string& word, int i)
    {
        TrieNode *iter = root;
        for(const char& ch: word)
        {
            TrieNode *&nxt = (iter -> children)[_char2int(ch)];
            if(!nxt)
                nxt = new TrieNode();
            iter = nxt;
        }
        iter -> w = i;
    }

    void match(const string& prefix, vector<bool>& setting) const
    {
        TrieNode *iter = root;
        for(const char& ch: prefix)
        {
            iter = (iter -> children)[_char2int(ch)];
            if(!iter)
                return;
        }
        dfs(iter, setting);
    }

    TrieNode* match(const string& prefix) const
    {
        TrieNode *iter = root;
        for(const char& ch: prefix)
        {
            iter = (iter -> children)[_char2int(ch)];
            if(!iter)
                iter = nullptr;
        }
        return iter;
    }

private:
    TrieNode *root;

    void dfs(TrieNode *root, vector<bool>& setting) const
    {
        for(TrieNode *child: (root -> children))
        {
            if(root -> w != -1)
                setting[root -> w] = true;
            if(child)
            {
                dfs(child, setting);
            }
        }
    }

    int  _char2int(const char& ch) const
    {
        return ch - 'a';
    }
};

class TrieSuffix
{
public:
    TrieSuffix()
    {
        root = new TrieNode();
    }

    ~TrieSuffix()
    {
        if(root)
        {
            delete root;
            root = nullptr;
        }
    }

    void insert(const string& word, int i)
    {
        TrieNode *iter = root;
        int n = word.size();
        for(int i = n - 1; i >= 0; --i)
        {
            char ch = word[i];
            TrieNode *&nxt = (iter -> children)[_char2int(ch)];
            if(!nxt)
                nxt = new TrieNode();
            iter = nxt;
        }
        iter -> w = i;
    }

    int match(const string& suffix, const vector<bool>& setting) const
    {
        TrieNode *iter = root;
        int n = suffix.size();
        for(int i = n - 1; i >= 0; --i)
        {
            char ch = suffix[i];
            iter = (iter -> children)[_char2int(ch)];
            if(!iter)
                return -1;
        }
        int ans = -1;
        dfs(iter, setting, ans);
        return ans;
    }

    TrieNode* match(const string& suffix) const
    {
        TrieNode *iter = root;
        int n = suffix.size();
        for(int i = n - 1; i >= 0; --i)
        {
            char ch = suffix[i];
            iter = (iter -> children)[_char2int(ch)];
            if(!iter)
                iter = nullptr;
        }
        return iter;
    }

private:
    TrieNode *root;

    void dfs(TrieNode *root, const vector<bool>& setting, int& ans) const
    {
        if(root -> w > ans && setting[root -> w])
            ans = root -> w;
        for(TrieNode *child: (root -> children))
        {
            if(child)
            {
                dfs(child, setting, ans);
            }
        }
    }

    int  _char2int(const char& ch) const
    {
        return ch - 'a';
    }
};

// 我们使用两个单词查找树找出所有前缀匹配的单词和后缀匹配的单词。再通过取集合的交集找到其中权值最大的单词，并返回权重。
// 然而，集合的元素可能会过大，导致超出时间限制。
class WordFilter {
public:
    WordFilter(vector<string>& words) {
        trie_prefix = new TriePrefix();
        trie_suffix = new TrieSuffix();
        n = words.size();
        for(int i = 0; i < n; ++i)
        {
            trie_prefix -> insert(words[i], i);
            trie_suffix -> insert(words[i], i);
        }
    }

    ~WordFilter()
    {
        if(trie_prefix)
        {
            delete trie_prefix;
            trie_prefix = nullptr;
        }
        if(trie_suffix)
        {
            delete trie_suffix;
            trie_suffix = nullptr;
        }
    }

    int f(string prefix, string suffix) {
        int pre_len = prefix.size(), suf_len = suffix.size();
        TrieNode *prefix_node = trie_prefix -> match(prefix);
        TrieNode *suffix_node = trie_suffix -> match(suffix);
        return match(prefix_node, pre_len, suffix_node, suf_len, n);
    }

private:
    TriePrefix *trie_prefix;
    TrieSuffix *trie_suffix;
    int n;
};

// 我们使用两个单词查找树找出所有前缀匹配的单词和后缀匹配的单词。再通过取集合的交集找到其中权值最大的单词，并返回权重。
// 然而，集合的元素可能会过大，导致超出时间限制。
