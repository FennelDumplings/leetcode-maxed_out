// prob336: Palindrome Pairs

/*
 * https://leetcode-cn.com/problems/palindrome-pairs/
 */

#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

bool check(const vector<int>& p, int i, int j)
{
    int m = i + j + 1;
    return p[m] >= j - i + 1;
}

struct TrieNode {
    const int ALPHABETS = 26;
    vector<TrieNode*> children;
    bool terminal;
    int idx;
    TrieNode()
    {
        idx = -1;
        terminal = false;
        children = vector<TrieNode*>(ALPHABETS, nullptr);
    }
    ~TrieNode(){}
};

class Trie {
public:
    Trie()
    {
        root = new TrieNode();
    }

    ~Trie()
    {
        delete_sub_tree(root);
    }

    void insert(string word, int j)
    {
        TrieNode *iter = root;
        for(const char c: word)
        {
            if(!(iter -> children[c - 'a']))
                (iter -> children)[c - 'a'] = new TrieNode();
            iter = (iter -> children)[c - 'a'];
        }
        iter -> terminal = true;
        iter -> idx = j;
    }

    bool search(string word)
    {
        const TrieNode* iter = find(word);
        return iter && iter -> terminal;
    }

    bool startsWith(string prefix)
    {
        return find(prefix) != nullptr;
    }

    void search_all_prefix(const string& word, const int i, vector<vector<int>>& result, const vector<string>& words, const vector<vector<int>>& p)
    {
        int m = word.size();
        TrieNode *iter = root;
        if(iter -> terminal)
        {
            int j = iter -> idx;
            if(i != j && check(p[i], 0, word.size() - 1))
                result.push_back({i, j});
        }
        for(int l = 0; l < m; ++l)
        {
            char ch = word[l];
            iter = (iter -> children)[ch - 'a'];
            if(iter == nullptr)
                break;
            if(iter -> terminal)
            {
                // 前缀 word[0..l] 找到
                // 判断 word[l+1..m-1] 是否构成回文
                int j = iter -> idx;
                if(i != j && check(p[i], l+1, m - l - 1))
                    result.push_back({i, j});
            }
        }
        // word 已经耗尽
        if(iter == nullptr)
            return;

        for(int c = 0; c < 26; ++c)
        {
            if(iter -> children[c])
            {
                dfs(iter -> children[c], i, result, words, m, p);
            }
        }
    }

    void dfs(TrieNode *node, const int i, vector<vector<int>>& result, const vector<string>& words, int m, const vector<vector<int>>& p)
    {
        if(node -> terminal)
        {
            int j = node -> idx;
            if(check(p[j], 0, words[j].size() - m - 1))
                result.push_back({i, j});
        }
        for(int c = 0; c < 26; ++c)
        {
            if(node -> children[c])
            {
                dfs(node -> children[c], i, result, words, m, p);
            }
        }
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

    const TrieNode* find(const string& prefix) const
    {
        const TrieNode* iter = root;
        for(const char c: prefix)
        {
            iter = (iter -> children)[c - 'a'];
            if(iter == nullptr)
                break;
        }
        return iter;
    }
};



class Solution {
public:
    vector<vector<int>> palindromePairs(vector<string>& words) {
        if(words.empty())
            return {};
        int n = words.size();
        if(n < 2)
            return {};

        vector<vector<int>> p(n);
        for(int k = 0; k < n; ++k)
        {
            int N = words[k].size();
            string t(N * 2 + 1, '#');

            for(int i = 0; i < N; ++i)
                t[2 * i + 1] = words[k][i];

            int m = t.size();
            p[k] = vector<int>(m, 1);
            int r = 0, c = 0;
            for(int i = 0; i < m; ++i)
            {
                int j = c * 2 - i;
                // 将不用扩展对比的部分直接置进 p[k][i] 中
                if(r > i)
                {
                    p[k][i] = min(p[k][j], r - i);
                }
                while(i - p[k][i] >= 0 && i + p[k][i] < m && t[i - p[k][i]] == t[i + p[k][i]])
                    p[k][i]++;
                if(i + p[k][i] > r)
                {
                    r = i + p[k][i];
                    c = i;
                }
            }
        }

        Trie *trie = new Trie();
        for(int i = 0; i < n; ++i)
        {
            reverse(words[i].begin(), words[i].end());
            trie -> insert(words[i], i);
            reverse(words[i].begin(), words[i].end());
        }

        vector<vector<int>> result;
        for(int i = 0; i < n; ++i)
        {
            string &word = words[i];
            int m = word.size();

            // 在搜索 word 的每个前缀，并更新答案
            trie -> search_all_prefix(word, i, result, words, p);
        }
        return result;
    }
};
