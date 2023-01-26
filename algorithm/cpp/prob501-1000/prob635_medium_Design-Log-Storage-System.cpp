// prob635: Design Log Storage System

/*
 * https://leetcode-cn.com/problems/design-log-storage-system/
 */

#include <string>
#include <vector>
#include <unordered_map>
#include <map>

using namespace std;

struct Node
{
    string type;
    vector<int> logs;
    map<string, Node*> children;
    Node(string type):type(type){}
};

class LogSystem {
public:
    LogSystem() {
        root = new Node("Root");
    }

    void put(int id, string timestamp) {
        int n = timestamp.size();
        int level = 0;
        Node *iter = root;
        int i = 0;
        while(i < n)
        {
            int j = timestamp.find_first_of(':', i);
            if(j == (int)string::npos)
                j = n;
            string key = timestamp.substr(i, j - i);
            ++level;
            if(!(iter -> children)[key])
                (iter -> children)[key] = new Node(LEVEL2TYPE[level]);
            iter = (iter -> children)[key];
            (iter -> logs).push_back(id);
            i = j + 1;
        }
    }

    vector<int> retrieve(string s, string e, string gra) {
        int level = TYPE2LEVEL.find(gra) -> second;
        vector<string> start_info = _parse(s);
        vector<string> end_info = _parse(e);
        vector<int> result;
        dfs(root, start_info, end_info, 0, level, true, true, result);
        return result;
    }

private:
    Node *root;

    void dfs(Node* node, const vector<string>& start_info, const vector<string>& end_info,
            int level, const int max_level, bool edge_left, bool edge_right, vector<int>& result)
    {
        // edge_prev true  前面顶到了右边界
        //           false 前面顶到了左边界
        if(level == max_level || (!edge_left && !edge_right))
        {
            result.insert(result.end(), (node -> logs).begin(), (node -> logs).end());
            return;
        }
        string start_key = start_info[level + 1];
        string end_key = end_info[level + 1];
        map<string, Node*>::iterator it;
        if(edge_left)
            it = (node -> children).lower_bound(start_key);
        else
            it = (node -> children).begin();
        map<string, Node*>::iterator end;
        if(edge_right)
            end = (node -> children).upper_bound(end_key);
        else
            end = (node -> children).end();
        while(it != end)
        {
            bool left_flag = edge_left && it -> first == start_key;
            bool right_flag = edge_right && it -> first == end_key;
            dfs(it -> second, start_info, end_info, level + 1, max_level,
                    left_flag, right_flag, result);
            ++it;
        }
    }

    vector<string> _parse(const string& s)
    {
        int n = s.size();
        int level = 0;
        int i = 0;
        vector<string> result(7);
        while(i < n)
        {
            int j = s.find_first_of(':', i);
            if(j == (int)string::npos)
                j = n;
            string key = s.substr(i, j - i);
            result[++level] = key;
            i = j + 1;
        }
        return result;
    }

    const vector<string> LEVEL2TYPE = {
        "Root",
        "Year",
        "Month",
        "Day",
        "Hour",
        "Minute",
        "Second"
    };

    const unordered_map<string, int> TYPE2LEVEL = {
        {"Root", 0},
        {"Year", 1},
        {"Month", 2},
        {"Day", 3},
        {"Hour", 4},
        {"Minute", 5},
        {"Second", 6}
    };
};
