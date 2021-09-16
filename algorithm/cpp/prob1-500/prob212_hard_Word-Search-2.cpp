// prob212: Word Search II

/*
 * Given a 2D board and a list of words from the dictionary, find all words in the board.
 * Each word must be constructed from letters of sequentially adjacent cell, where "adjacent" cells are those
 * horizontally or vertically neighboring. The same letter cell may not be used more than once in a word.
 */

/*
 * Example:
 * Input:
 * board = [
 *   ['o','a','a','n'],
 *   ['e','t','a','e'],
 *   ['i','h','k','r'],
 *   ['i','f','l','v']
 * ]
 * words = ["oath","pea","eat","rain"]
 * Output: ["eat","oath"]
 */

/*
 * Note:
 * All inputs are consist of lowercase letters a-z.
 * The values of words are distinct.
 */

#include <string>
#include <vector>

using namespace std;

const int ALPHABETS = 26;

struct TrieNode
{
    bool terminate;
    vector<TrieNode*> children;
    TrieNode()
    {
        terminate = false;
        children = vector<TrieNode*>(ALPHABETS, nullptr);
    }
    ~TrieNode(){}
};

class Trie
{
private:
    void delete_sub_tree(TrieNode* node)
    {
        for(TrieNode *child: node -> children)
        {
            if(child)
                delete_sub_tree(child);
            delete child;
            child = nullptr;
        }
    }

public:
    Trie()
    {
        root = new TrieNode();
    }

    ~Trie()
    {
        if(root)
            delete_sub_tree(root);
        delete root;
        root = nullptr;
    }

    void insert(const string& word)
    {
        TrieNode *iter = root;
        for(const char& ch: word)
        {
            TrieNode *&nxt = (iter -> children)[ch - 'a'];
            if(!nxt)
                nxt = new TrieNode();
            iter = nxt;
        }
        iter -> terminate = true;
    }

    TrieNode* get_root()
    {
        return root;
    }

    TrieNode* get_nxt(char ch, TrieNode* iter)
    {
        return (iter -> children)[ch - 'a'];
    }

private:
    TrieNode *root;
};


class Solution {
public:
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        if(board.empty() || words.empty()) return vector<string>();
        int n = board.size(), m = board[0].size();
        vector<vector<bool> > visited(n, vector<bool>(m, false));
        vector<string> result;
        string cur = "";
        Trie *trie  = new Trie();
        for(const string& word: words)
            trie -> insert(word);
        TrieNode *iter = trie -> get_root();
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < m; ++j)
            {
                visited.assign(n, vector<bool>(m, false));
                visited[i][j] = true;
                cur += board[i][j];
                dfs(board, visited, i, j, cur, result, trie, iter);
                cur.pop_back();
                visited[i][j] = false;
            }
        delete trie;
        trie = nullptr;
        return result;
    }

private:
    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};

    void dfs(const vector<vector<char> >& board, vector<vector<bool> >& visited, int i, int j,
            string& cur, vector<string>& result, Trie *trie, TrieNode* iter)
    {
        TrieNode *nxt = trie -> get_nxt(board[i][j], iter);
        if(!nxt) return;
        iter = nxt;
        if(iter -> terminate)
        {
            result.push_back(cur);
            iter -> terminate = false;
        }

        int n = board.size(), m = board[0].size();
        for(int d = 0; d < 4; ++d)
        {
            int x = i + dx[d], y = j + dy[d];
            if(x < 0 || x >= n || y < 0 || y >= m || visited[x][y])
                continue;
            visited[x][y] = true;
            cur += board[x][y];
            dfs(board, visited, x, y, cur, result, trie, iter);
            cur.pop_back();
            visited[x][y] = false;
        }
    }
};
