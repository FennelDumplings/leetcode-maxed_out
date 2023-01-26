// prob425: Word Squares

/*
 * https://leetcode-cn.com/problems/word-squares/
 */

#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

class Solution_2 {
public:
    vector<vector<string>> wordSquares(vector<string>& words) {
        mappings = vector<unordered_map<string, vector<string>>*>(1, nullptr);
        for(int i = 1; i <= 5; ++i)
        {
            unordered_map<string, vector<string>> *mapping = new unordered_map<string, vector<string>>();
            mappings.push_back(mapping);
        }
        vector<vector<string>> result;
        for(const string& word: words)
        {
            int l = word.size();
            if(l == 1)
            {
                result.push_back({word});
                continue;
            }
            // l = 2..5
            // 记录 1~l-1 的前缀
            for(int len = 0; len <= l - 1; ++len)
            {
                string prefix = word.substr(0, len);
                (*mappings[l])[prefix].push_back(word);
            }
        }
        for(int l = 2; l <= 5; ++l)
        {
            // 考虑 len 前缀的所有串
            vector<string> item(l);
            for(string s: (*mappings[l])[""])
            {
                item[0] = s;
                dfs(item, result, 1);
            }
        }
        return result;
    }

private:
    vector<unordered_map<string, vector<string>>*> mappings;

    void dfs(vector<string>& item, vector<vector<string>>& result, int row)
    {
        int l = item.size();
        if(row == l)
        {
            result.push_back(item);
            return;
        }
        int len = row; // 考虑前缀的长度
        string prefix(len, ' ');
        for(int i = 0; i < len; ++i)
        {
            prefix[i] = item[i][row];
        }
        for(string word: (*mappings[l])[prefix])
        {
            item[row] = word;
            dfs(item, result, row + 1);
        }
    }
};


// Trie
const int ALPHABET = 26;

struct TrieNode
{
    vector<string> words;
    vector<TrieNode*> children;
    TrieNode()
    {
        words = vector<string>();
        children = vector<TrieNode*>(ALPHABET);
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

class Trie
{
public:
    Trie()
    {
        root = new TrieNode();
    }

    ~Trie()
    {
        if(root)
        {
            delete root;
            root = nullptr;
        }
    }

    void insert(const string& word)
    {
        _insert(root, word, 0);
    }

    vector<string> search_prefix(const string& prefix)
    {
        TrieNode *p = _find(root, prefix, 0);
        if(!p)
            return {};
        return p -> words;
    }

private:
    TrieNode *root;

    void _insert(TrieNode* node, const string& word, int pos)
    {
        int l = word.size();
        if(pos == l)
            return;
        (node -> words).push_back(word);
        if(!(node -> children)[word[pos] - 'a'])
            (node -> children)[word[pos] - 'a'] = new TrieNode();
        _insert((node -> children)[word[pos] - 'a'], word, pos + 1);
    }

    TrieNode* _find(TrieNode* node, const string& prefix, int pos)
    {
        int n = prefix.size();
        if(n == pos)
            return node;
        if(!(node -> children)[prefix[pos] - 'a'])
            return nullptr;
        return _find((node -> children)[prefix[pos] - 'a'], prefix, pos + 1);

    }
};

class Solution {
public:
    vector<vector<string>> wordSquares(vector<string>& words) {
        mappings = vector<Trie*>(1, nullptr);
        for(int i = 1; i <= 5; ++i)
        {
            Trie *trie = new Trie();
            mappings.push_back(trie);
        }
        vector<vector<string>> result;
        for(const string& word: words)
        {
            int l = word.size();
            if(l == 1)
            {
                result.push_back({word});
                continue;
            }
            // l = 2..5
            // 记录 1~l-1 的前缀
            mappings[l] -> insert(word);
        }
        for(int l = 2; l <= 5; ++l)
        {
            // 考虑 len 前缀的所有串
            vector<string> item(l);
            for(string s: mappings[l] -> search_prefix(""))
            {
                item[0] = s;
                dfs(item, result, 1);
            }
        }
        return result;
    }

private:
    vector<Trie*> mappings;

    void dfs(vector<string>& item, vector<vector<string>>& result, int row)
    {
        int l = item.size();
        if(row == l)
        {
            result.push_back(item);
            return;
        }
        int len = row; // 考虑前缀的长度
        string prefix(len, ' ');
        for(int i = 0; i < len; ++i)
        {
            prefix[i] = item[i][row];
        }
        for(string word: mappings[l] -> search_prefix(prefix))
        {
            item[row] = word;
            dfs(item, result, row + 1);
        }
    }
};
