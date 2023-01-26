// prob588: Design In-Memory File System

/*
 * https://leetcode-cn.com/problems/design-in-memory-file-system/
 */

#include <vector>
#include <string>
#include <map>

using namespace std;

struct Node
{
    bool fold;
    string content; // fold 为 false 时有意义
    string name;
    map<string, Node*> children; // fold 为 true 时有意义
    Node(bool fold, string name=""):fold(fold),name(name){}
};

class FileSystem {
public:
    FileSystem() {
        root = new Node(true);
    }

    vector<string> ls(string path) {
        auto it = _find(path);
        vector<string> result;
        if(it -> fold)
            for(auto item: it -> children)
                result.push_back(item.first);
        else
            result.push_back(it -> name);
        return result;
    }

    void mkdir(string path) {
        _find(path);
    }

    void addContentToFile(string filePath, string content) {
        auto it = _find(filePath);
        if(it -> fold == true) // 首次创建
            it -> fold = false;
        it -> content += content;
    }

    string readContentFromFile(string filePath) {
        auto it = _find(filePath);
        return it -> content;
    }

private:
    Node *root;

    Node* _find(const string& path)
    {
        Node *iter = root;
        int i = 0;
        int n = path.size();
        while(i + 1 < n)
        {
            int j = i + 1;
            while(j < n && path[j] != '/')
                ++j;
            string s = path.substr(i + 1, j - (i + 1));
            if(!(iter -> children)[s])
                (iter -> children)[s] = new Node(true, s);
            iter = (iter -> children)[s];
            i = j;
        }
        return iter;
    }
};
