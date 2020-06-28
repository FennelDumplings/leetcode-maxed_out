

#include <string>
#include <unordered_set>
#include <unordered_map>

using namespace std;

class Solution {
public:
    bool isPathCrossing(string path) {
        unordered_map<char, int> d_map;
        // {{'N', 0}, {'S', 1}, {'E', 2}, {'W', 3}}
        d_map['N'] = 0;
        d_map['S'] = 1;
        d_map['E'] = 2;
        d_map['W'] = 3;
        unordered_set<int> visited;
        int x = 0, y = 0;
        visited.insert(x * 1e4 + y);
        for(char& ch: path)
        {
            int d = d_map[ch];
            x = x + dx[d];
            y = y + dy[d];
            if(visited.find(x * 1e4 + y) != visited.end())
                return true;
            visited.insert(x * 1e4 + y);
        }
        return false;
    }

private:
    // {'N', 'S', 'E', 'W}
    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};
    using PII = pair<int, int>;
};
