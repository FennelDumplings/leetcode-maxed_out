// prob648: Replace Words

/*
 * In English, we have a concept called root, which can be followed by some other words to form another longer word - let's
 * call this word successor. For example, the root an, followed by other, which can form another word another.
 * Now, given a dictionary consisting of many roots and a sentence. You need to replace all the successor in the sentence
 * with the root forming it. If a successor has many roots can form it, replace it with the root with the shortest length.
 * You need to output the sentence after the replacement.
 */

/*
 * Example 1:
 * Input: dict = ["cat","bat","rat"], sentence = "the cattle was rattled by the battery"
 * Output: "the cat was rat by the bat"
 */

/*
 * Constraints:
 * The input will only have lower-case letters.
 * 1 <= dict.length <= 1000
 * 1 <= dict[i].length <= 100
 * 1 <= sentence words number <= 1000
 * 1 <= sentence words length <= 1000
 */

#include <vector>
#include <string>
#include <sstream>

using namespace std;

const int ALPHABET = 26;

struct TrieNode
{
    bool terminate;
    vector<TrieNode*> children;
    TrieNode()
    {
        terminate = false;
        children = vector<TrieNode*>(ALPHABET, nullptr);
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

    void insert(const string& word_root)
    {
        TrieNode *iter = root;
        for(const char& ch: word_root)
        {
            TrieNode *&next = (iter -> children)[_char2int(ch)];
            if(!next)
                next = new TrieNode;
            iter = next;
        }
        iter -> terminate = true;
    }

    string word_root(const string& word)
    {
        TrieNode *iter = root;
        string result = "";
        for(const char& ch: word)
        {
            TrieNode *& next = (iter -> children)[_char2int(ch)];
            if(!next) return word;
            result += ch;
            if(next -> terminate) return result;
            iter = next;
        }
        return word;
    }

private:
    TrieNode *root;

    int _char2int(const char& ch)
    {
        return ch - 'a';
    }
};

class Solution {
public:
    string replaceWords(vector<string>& dict, string sentence) {
        Trie trie;
        for(const string& word_root: dict)
        {
            trie.insert(word_root);
        }
        string result;
        stringstream ss;
        ss << sentence;
        string word;
        while(ss >> word)
        {
            result += trie.word_root(word);
            result += ' ';
        }
        result.pop_back();
        return result;
    }
};
