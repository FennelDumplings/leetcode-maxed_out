// prob1233: Remove Sub-Folders from the Filesystem

/*
 * https://leetcode-cn.com/problems/remove-sub-folders-from-the-filesystem/
 */

#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

struct TrieNode
{
    unordered_map<string, TrieNode*> children;
    bool terminate;
    TrieNode(bool flag):terminate(flag){}
};

class Solution {
public:
    vector<string> removeSubfolders(vector<string>& folder) {
        root = new TrieNode(false);
        for(const string& s: folder)
        {
            int left = 1;
            int n = s.size();
            TrieNode *iter = root;
            while(left < n)
            {
                int right = left;
                while(right < n && s[right] != '/')
                    ++right;
                string v = s.substr(left, right - left);
                if((iter -> children).count(v) == 0)
                    (iter -> children)[v] = new TrieNode(false);
                iter = iter -> children[v];
                left = right + 1;
            }
            iter -> terminate = true;
        }
        vector<string> result;
        string path;
        dfs(root, path, result);
        return result;
    }

private:
    TrieNode *root;

    void dfs(TrieNode* node, string& path, vector<string>& result)
    {
        if(node -> terminate)
        {
            result.push_back(path);
            return;
        }
        for(auto child: node -> children)
        {
            if(child.second)
            {
                path += '/' + child.first;
                dfs(child.second, path, result);
                path.erase(path.find_last_of('/'));
            }
        }
    }
};
