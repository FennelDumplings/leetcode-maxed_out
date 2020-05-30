// prob642: Design Search Autocomplete System

/*
 * Design a search autocomplete system for a search engine. Users may input a sentence (at least one word and end with a
 * special character '#'). For each character they type except '#', you need to return the top 3 historical hot sentences
 * that have prefix the same as the part of sentence already typed. Here are the specific rules:
 *
 * The hot degree for a sentence is defined as the number of times a user typed the exactly same sentence before.
 * The returned top 3 hot sentences should be sorted by hot degree (The first is the hottest one). If several
 * sentences have the same degree of hot, you need to use ASCII-code order (smaller one appears first).
 * If less than 3 hot sentences exist, then just return as many as you can.
 * When the input is a special character, it means the sentence ends, and in this case, you need to return an empty list.
 * Your job is to implement the following functions:
 *
 * The constructor function:
 *
 * AutocompleteSystem(String[] sentences, int[] times): This is the constructor. The input is historical data.
 * Sentences is a string array consists of previously typed sentences. Times is the corresponding times a
 * sentence has been typed. Your system should record these historical data.
 *
 * Now, the user wants to input a new sentence. The following function will provide the next character the user types:
 *
 * List<String> input(char c): T/e input c is the next character typed by the user. The character will only be lower-case
 * letters ('a' to 'z'), blank space (' ') or a special character ('#'). Also, the previously typed sentence should be recorded in your
 * system. The output will be the top 3 historical hot sentences that have prefix the same as the part of sentence already typed.
 */

/*
 * Example:
 * Operation: AutocompleteSystem(["i love you", "island","ironman", "i love leetcode"], [5,3,2,2])
 * The system have already tracked down the following sentences and their corresponding times:
 * "i love you" : 5 times
 * "island" : 3 times
 * "ironman" : 2 times
 * "i love leetcode" : 2 times
 * Now, the user begins another search:
 * Operation: input('i')
 * Output: ["i love you", "island","i love leetcode"]
 * Explanation:
 * There are four sentences that have prefix "i". Among them, "ironman" and "i love leetcode" have same hot degree. Since ' ' has ASCII code 32 and 'r' has ASCII code 114, "i love leetcode" should be in front of "ironman". Also we only need to output top 3 hot sentences, so "ironman" will be ignored.
 * Operation: input(' ')
 * Output: ["i love you","i love leetcode"]
 * Explanation:
 * There are only two sentences that have prefix "i ".
 * Operation: input('a')
 * Output: []
 * Explanation:
 * There are no sentences that have prefix "i a".
 * Operation: input('#')
 * Output: []
 * Explanation:
 * The user finished the input, the sentence "i a" should be saved as a historical sentence in system. And the following input will be counted as a new search.
 */

/*
 * Note:
 * The input sentence will always start with a letter and end with '#', and only one blank space will exist between two words.
 * The number of complete sentences that to be searched won't exceed 100. The length of each sentence including those in the historical data won't exceed 100.
 * Please use double-quote instead of single-quote when you write test cases even for a character input.
 * Please remember to RESET your class variables declared in class AutocompleteSystem, as static/class variables are persisted across multiple test cases. Please see here for more details.
 */

#include <vector>
#include <string>
#include <queue>
#include <stack>

using namespace std;

const int ALPHABET = 27;

struct TrieNode
{
    int cnt;
    vector<TrieNode*> children;
    TrieNode()
    {
        cnt = 0;
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
        input = root;
        cur = "";
    }

    ~Trie()
    {
        if(root)
        {
            delete root;
            root = nullptr;
            input = nullptr;
        }
    }

    void insert(const string& sentence, int cnt)
    {
        TrieNode *iter = root;
        for(const char ch: sentence)
        {
            TrieNode *&nxt = (iter -> children)[_char2int(ch)];
            if(!nxt)
                nxt = new TrieNode();
            iter = nxt;
        }
        iter -> cnt = cnt;
    }

    vector<string> auto_complete(char ch)
    {
        if(ch == '#')
        {
            ++(input -> cnt);
            cur = "";
            input = root;
            return vector<string>();
        }
        cur += ch;
        TrieNode *&nxt = (input -> children)[_char2int(ch)];
        if(!nxt)
        {
            nxt = new TrieNode();
            input = nxt;
            return vector<string>();
        }
        input = nxt;
        priority_queue<PSI, vector<PSI>, Cmp> pq; // 容量为 3 的最小堆
        dfs(input, cur, pq);
        vector<string> result;
        stack<string> st;
        while(!pq.empty())
        {
            st.push(pq.top().first);
            pq.pop();
        }
        while(!st.empty())
        {
            result.push_back(st.top());
            st.pop();
        }
        return result;
    }

private:
    TrieNode *root;
    string cur;
    TrieNode *input;

    using PSI = pair<string, int>; // sentence, cnt

    struct Cmp
    {
        bool operator()(const PSI& psi1, const PSI& psi2)
        {
            // psi1 比 psi2 小：
            // psi1.second < psi2.second
            // psi1.first > psi2.first
            if(psi1.second == psi2.second)
                return psi1.first < psi2.first;
            return psi1.second > psi2.second;
        }
    };

    void dfs(TrieNode* root, string& cur, priority_queue<PSI, vector<PSI>, Cmp>& pq)
    {
        if(root -> cnt > 0)
        {
            if(pq.size() < 3)
                pq.push(PSI(cur, root -> cnt));
            else
            {
                Cmp cmp;
                if(!cmp(pq.top(), PSI(cur, root -> cnt)))
                {
                    pq.push(PSI(cur, root -> cnt));
                    pq.pop();
                }
            }
        }
        for(int i = 0; i < 27; ++i)
        {
            TrieNode *child = (root -> children)[i];
            if(i < 26) cur += 'a' + i;
            else cur += ' ';
            if(child)
                dfs(child, cur, pq);
            cur.pop_back();
        }
    }

    int _char2int(const char& ch)
    {
        if(ch == ' ') return 26;
        return ch - 'a';
    }
};

class AutocompleteSystem {
public:
    AutocompleteSystem(vector<string>& sentences, vector<int>& times) {
        trie = new Trie();
        int n = sentences.size();
        for(int i = 0; i < n; ++i)
            trie -> insert(sentences[i], times[i]);
    }

    vector<string> input(char c) {
        return trie -> auto_complete(c);
    }

private:
    Trie *trie;
};
