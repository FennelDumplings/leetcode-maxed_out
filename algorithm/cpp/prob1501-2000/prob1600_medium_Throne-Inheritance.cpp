
#include <vector>
#include <unordered_map>
#include <string>

using namespace std;

class ThroneInheritance {
public:
    ThroneInheritance(string kingName) {
        root = new TreeNode(kingName);
        mapping[kingName] = root;;
    }

    void birth(string parentName, string childName) {
        TreeNode *son = new TreeNode(childName);
        (mapping[parentName] -> children).push_back(son);
        mapping[childName] = son;
    }

    void death(string name) {
        mapping[name] -> die = true;
    }

    vector<string> getInheritanceOrder() {
        vector<string> result;
        dfs(root, result);
        return result;
    }

private:
    struct TreeNode
    {
        vector<TreeNode*> children;
        string name;
        bool die;
        TreeNode(string& name):name(name),die(false){}
    };

    unordered_map<string, TreeNode*> mapping;

    TreeNode *root;

    void dfs(TreeNode* node, vector<string>& result)
    {
        if(!node -> die)
            result.emplace_back(node -> name);
        for(TreeNode *son: node -> children)
            dfs(son, result);
    }
};
