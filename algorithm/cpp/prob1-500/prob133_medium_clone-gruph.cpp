// prob133: Clone Graph

/*
 *
 * Given a reference of a node in a connected undirected graph.
 * Return a deep copy (clone) of the graph.
 * Each node in the graph contains a val (int) and a list (List[Node]) of its neighbors.
 *
 * class Node {
 *     public int val;
 *     public List<Node> neighbors;
 * }
 */

#include <vector>
#include <queue>
#include <unordered_map>

using namespace std;

class Node {
public:
    int val;
    vector<Node*> neighbors;

    Node() {
        val = 0;
        neighbors = vector<Node*>();
    }

    Node(int _val) {
        val = _val;
        neighbors = vector<Node*>();
    }

    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};

// 邻接表的 BFS
class Solution {
public:
    Node* cloneGraph(Node* node) {
        if(!node) return nullptr;

        queue<Node*> q;
        queue<Node*> q_output;
        unordered_map<Node*, Node*> mapping; // 已经访问过的节点

        Node *head = new Node(node -> val);
        q_output.push(head);
        q.push(node);
        mapping[node] = head;
        while(!q.empty())
        {
            Node *u = q.front();
            Node *u_output = q_output.front();
            q.pop();
            q_output.pop();
            for(Node *v: u -> neighbors)
            {
                if(mapping.find(v) == mapping.end()) // v 未被访问过
                {
                    Node *tmp = new Node(v -> val);
                    mapping[v] = tmp;
                    q.push(v);
                    q_output.push(mapping[v]);
                }
                (u_output -> neighbors).push_back(mapping[v]);
            }
        }
        return head;
    }
};

// 邻接表的 DFS
class Solution_2 {
public:
    Node* cloneGraph(Node* node) {
        if(!node) return nullptr;

        unordered_map<Node*, Node*> mapping; // 已经访问过的节点

        Node *head = new Node(node -> val);
        mapping[node] = head; // DFS 之前先对点进行标记
        Node *iter = node, *iter_output = head;
        dfs(iter, iter_output, mapping);
        return head;
    }

private:
    void dfs(Node* iter, Node* iter_output, unordered_map<Node*, Node*>& mapping)
    {
        // iter 在进本次 dfs 之前已经被标记过
        // 对每一个相邻节点：
        //     若未访问过，则先建点，再连边，再 DFS 进去
        //     若已经被访问过，则直接连边(不DFS)
        for(Node *nxt: iter -> neighbors)
        {
            if(mapping.find(nxt) == mapping.end())
            {
                Node *tmp = new Node(nxt -> val);
                mapping[nxt] = tmp;
                (iter_output -> neighbors).push_back(tmp);
                dfs(nxt, tmp, mapping);
            }
            else
            {
                (iter_output -> neighbors).push_back(mapping[nxt]);
            }
        }
    }
};
