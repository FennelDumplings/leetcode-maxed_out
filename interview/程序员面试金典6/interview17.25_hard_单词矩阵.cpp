// interview17.25: 单词矩阵

/*
 * https://leetcode-cn.com/problems/word-rectangle-lcci/
 */

#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <set>
#include <functional>

using namespace std;

class Solution {
public:
    vector<string> maxRectangle(vector<string>& words) {
        int max_l = 0;
        for(const string& word: words)
            max_l = max(max_l, (int)word.size());
        mappings = vector<unordered_map<string, vector<string>>*>(max_l + 1, nullptr);
        for(int l = 0; l <= max_l; ++l)
            mappings[l] = new unordered_map<string, vector<string>>();
        for(const string& word: words)
        {
            int l = word.size();
            for(int len = 0; len <= l; ++len)
            {
                string prefix = word.substr(0, len);
                (*mappings[l])[prefix].push_back(word);
            }
        }
        vector<string> result;
        int n = 0, m = 0;
        for(int w = max_l; w >= 1; --w)
        {
            if(w * w < m * n)
                break;
            if((*mappings[w])[""].empty())
                continue;
            vector<string> item(w, string(w, ' '));
            for(int h = w; h >= 1; --h)
            {
                if(w * h <= m * n)
                    break;
                if(dfs(item, 0))
                {
                    result = item;
                    n = h;
                    m = w;
                    break;
                }
                item.pop_back();
            }
        }
        return result;
    }

private:
    vector<unordered_map<string, vector<string>>*> mappings;

    bool dfs(vector<string>& item, int row)
    {
        // 当前准备选第 row 行单词
        int h = item.size(), w = item[0].size();
        if(h == row)
            return true;
        int len = row + 1; // 选择第 row 行单词时需要从 mappings[h] 中考查的前缀的长度
        // 从 mappings[w] 中选词
        for(const string& word: (*mappings[w])[""])
        {
            item[row] = word;
            bool flag = true;
            for(int j = 0; j < w; ++j)
            {
                string prefix(len, ' ');
                for(int i = 0; i < len; ++i)
                    prefix[i] = item[i][j];
                if((*mappings[h])[prefix].empty())
                {
                    flag = false;
                    break;
                }
            }
            if(flag)
                if(dfs(item, row + 1))
                    return true;
        }
        return false;
    }
};


// Trie
struct TrieNode {
  TrieNode(TrieNode* p = nullptr):parent(p) {}
  TrieNode* children[26]{};
  TrieNode* parent;
  bool word = false;
};
class Trie {
public:
    TrieNode root;
    Trie() {
      root.parent = &root;
    }
    void insert(const string& word) {
      auto cur = &root;
      for (auto n : word) {
        if (cur->children[n - 'a'] == nullptr) {
          cur->children[n - 'a'] = new TrieNode(cur);
        }
        cur = cur->children[n - 'a'];
      }
      cur->word = true;
    }
};

class Solution {
      vector<string> realres;
      int realsz = 0;
      Trie tree;
public:
    void dfs(vector<string>& res, vector<string>& w, vector<TrieNode*>& nodes) {
      auto l = w[0].size();
      //cout << l << " " << nodes.size() << endl;
      if (res.size()) {
        auto n = 0;
        for (int i = 0; i != l; ++i) {
          auto tmp = nodes[i];
          nodes[i] = nodes[i]->children[res.back()[i] - 'a'];
          if (!nodes[i]) {
            for (int k = 0; k != i; ++k) {
              nodes[k] = nodes[k]->parent;
            }
            nodes[i] = tmp;
            return;
          }
          if (nodes[i]->word) ++n;
        }
        if (n == l) {
          auto sz = res.size() * res[0].size();
          if (sz > realsz) {
            realres = res;
            realsz = sz;
          }
        }
      }
      for (int n = 0; n != w.size(); ++n) {
        res.emplace_back(w[n]);
        //cout << w[n].size() << endl;
        dfs(res, w, nodes);
        res.pop_back();
      }
      for (auto& n : nodes) {
        n = n->parent;
      }
    }
    vector<string> maxRectangle(vector<string>& words) {
      vector<vector<string>> w(101);
      for (auto& n : words) {
        w[n.size()].emplace_back(n);
        tree.insert(n);
      }
      vector<string> res;
      auto sz = 0;
      for (auto iter = w.rbegin(); iter != w.rend(); ++iter) {
        if (iter->empty() || (*iter)[0].size() * iter->size() <= realsz) continue;
        vector<string> tmp;
        vector<TrieNode*> nodes((*iter)[0].size(), &tree.root);
        dfs(tmp, *iter, nodes);
      }
      return {begin(realres), end(realres)};
    }
};
