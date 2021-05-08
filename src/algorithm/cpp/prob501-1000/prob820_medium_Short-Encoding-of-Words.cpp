// prob820: Short Encoding of Words

/*
 *
 * Given a list of words, we may encode it by writing a reference string S and a list of indexes A.
 * For example, if the list of words is ["time", "me", "bell"], we can write it as S = "time#bell#" and indexes = [0, 2, 5].
 * Then for each index, we will recover the word by reading from the reference string from that index until we reach a "#" character.
 * What is the length of the shortest reference string S possible that encodes the given words?
 */

/*
 * Example:
 * Input: words = ["time", "me", "bell"]
 * Output: 10
 * Explanation: S = "time#bell#" and indexes = [0, 2, 5].
 */

/*
 * Note:
 * 1 <= words.length <= 2000.
 * 1 <= words[i].length <= 7.
 * Each word has only lowercase letters.
 */

#include <vector>
#include <string>

using namespace std;

struct TrieNode {
    const int ALPHABET = 26;
    vector<TrieNode*> children;
    bool terminate;
    TrieNode()
    {
        terminate = false;
        children = vector<TrieNode*>(ALPHABET, nullptr);
    }
    ~TrieNode()
    {
        for(TrieNode *child: children)
            if(child)
                delete child;
    }
};

class Trie {
public:
    Trie() {
        root = new TrieNode();
    }

    ~Trie() {
        delete root;
    }

    void insert(string& word)
    {
        int n = word.size();
        TrieNode *iter = root;
        for(int i = n - 1; i >= 0; --i)
        {
            if(!(iter -> children)[_to_int(word[i])])
                (iter -> children)[_to_int(word[i])] = new TrieNode();
            iter = (iter -> children)[_to_int(word[i])];
        }
        iter -> terminate = true;
    }

    int stat()
    {
        int level = 0;
        int result = 0;
        dfs(root, level, result);
        return result;
    }

private:
    TrieNode *root;

    void dfs(TrieNode* root, int level, int& result)
    {
        if(_is_leaf(root))
        {
            result += level + 1;
            return;
        }

        for(TrieNode *child: root -> children)
        {
            if(child)
                dfs(child, level + 1, result);
        }
    }

    bool _is_leaf(TrieNode* p)
    {
        for(TrieNode *child: (p -> children))
            if(child)
                return false;
        return true;
    }

    int _to_int(char ch)
    {
        return ch - 'a';
    }
};

class Solution {
public:
    int minimumLengthEncoding(vector<string>& words) {
        Trie trie;
        for(string word: words)
            trie.insert(word);
        return trie.stat();
    }
};
