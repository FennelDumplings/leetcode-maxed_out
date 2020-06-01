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

    void match(const string& prefix, unordered_set<int>& setting) const
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

private:
    TrieNode *root;

    void dfs(TrieNode *root, unordered_set<int>& setting) const
    {
        for(TrieNode *child: (root -> children))
        {
            if(root -> w != -1)
                setting.insert(root -> w);
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

    int match(const string& suffix, const unordered_set<int>& setting) const
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

private:
    TrieNode *root;

    void dfs(TrieNode *root, const unordered_set<int>& setting, int& ans) const
    {
        if(root -> w > ans && setting.find(root -> w) != setting.end())
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

class WordFilter {
public:
    WordFilter(vector<string>& words) {
        trie_prefix = new TriePrefix();
        trie_suffix = new TrieSuffix();
        int n = words.size();
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
        unordered_set<int> setting;
        trie_prefix -> match(prefix, setting);
        return trie_suffix -> match(suffix, setting);
    }

private:
    TriePrefix *trie_prefix;
    TrieSuffix*trie_suffix;
};
