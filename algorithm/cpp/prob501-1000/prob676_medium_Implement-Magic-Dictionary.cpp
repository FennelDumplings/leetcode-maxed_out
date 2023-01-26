// prob676: Implement Magic Dictionary

/*
 * Implement a magic directory with buildDict, and search methods.
 * For the method buildDict, you'll be given a list of non-repetitive words to build a dictionary.
 * For the method search, you'll be given a word, and judge whether if you modify exactly one character into
 * another character in this word, the modified word is in the dictionary you just built.
 */

/*
 * Example 1:
 * Input: buildDict(["hello", "leetcode"]), Output: Null
 * Input: search("hello"), Output: False
 * Input: search("hhllo"), Output: True
 * Input: search("hell"), Output: False
 * Input: search("leetcoded"), Output: False
 */

/*
 * Note:
 * You may assume that all the inputs are consist of lowercase letters a-z.
 * For contest purpose, the test data is rather small by now. You could think about highly efficient algorithm after the contest.
 * Please remember to RESET your class variables declared in class MagicDictionary, as static/class variables are persisted across multiple test cases. Please see here for more details.
 */

#include <vector>
#include <string>

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
        TrieNode *iter = root;
        for(const char& ch: word)
        {
            TrieNode *&nxt = (iter -> children)[_char2int(ch)];
            if(!nxt)
                nxt = new TrieNode();
            iter = nxt;
        }
        iter -> terminate = true;
    }

    bool search(const string& word) const
    {
        return _search(root, word, 0, false);
    }

private:
    TrieNode *root;

    int _char2int(const char& ch) const
    {
        return ch - 'a';
    }

    bool _search(TrieNode* root, const string& word, int idx, bool changed) const
    {
        int n = word.size();
        if(idx == n)
        {
            if(root -> terminate && changed)
                return true;
            else
                return false;
        }

        TrieNode *nxt = (root -> children)[_char2int(word[idx])];
        if(nxt)
            if(_search(nxt, word, idx + 1, changed))
                return true;
        // nxt 存在，但返回 false 或者不存在 nxt
        // 此后要变当前字符
        if(changed) return false;

        for(TrieNode *child: (root -> children))
        {
            if(!child || child == nxt) continue;
            if(_search(child, word, idx + 1, true))
                return true;
        }
        return false;
    }
};

class MagicDictionary {
public:
    /** Initialize your data structure here. */
    MagicDictionary() {
        trie = new Trie();
    }

    ~MagicDictionary() {
        if(trie)
        {
            delete trie;
            trie = nullptr;
        }
    }

    /** Build a dictionary through a list of words */
    void buildDict(vector<string> dict) {
        for(const string& word: dict)
            trie -> insert(word);
    }

    /** Returns if there is any word in the trie that equals to the given word after modifying exactly one character */
    bool search(string word) {
        return trie -> search(word);
    }

private:
    Trie *trie;
};
