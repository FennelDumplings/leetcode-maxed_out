// prob1410: HTML Entity Parser

/*
 * https://leetcode-cn.com/problems/html-entity-parser/
 */

#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

struct TrieNode
{
    unordered_map<char, TrieNode*> children;
    string val;
    TrieNode(){}
};

class Trie
{
public:
    Trie()
    {
        root = new TrieNode();
    }

    void insert(const string& key, const string& val)
    {
        TrieNode *iter = root;
        for(const char &ch: key)
        {
            if(!(iter -> children)[ch])
                (iter -> children)[ch] = new TrieNode();
            iter = (iter -> children)[ch];
        }
        iter -> val = val;
    }

    string search(const string& s, int& i)
    {
        // s[i] == '&', 从 s[i] 开始推进，若匹配到，返回匹配的字符，未匹配到返回 ""
        // i 的推进通过引用直接返回给调用方
        int n = s.size();
        TrieNode *iter = root;
        while(i < n && (iter -> children)[s[i]])
        {
            iter = (iter -> children)[s[i]];
            if(!(iter -> val).empty())
                return iter -> val;
            ++i;
        }
        return "";
    }

private:
    TrieNode *root;
};

class Solution {
public:
    string entityParser(string text) {
        Trie *trie = new Trie();
        trie -> insert("&quot;", "\"");
        trie -> insert("&apos;", "'");
        trie -> insert("&amp;", "&");
        trie -> insert("&gt;", ">");
        trie -> insert("&lt;", "<");
        trie -> insert("&frasl;", "/");
        int n = text.size();
        int i = 0;
        string result;
        while(i < n)
        {
            if(text[i] != '&')
                result += text[i++];
            else
            {
                int j = i;
                string alter = trie -> search(text, i);
                if(alter.empty())
                    result += text.substr(j, i - j + 1);
                else
                    result += alter;
                ++i;
            }
        }
        return result;
    }
};
