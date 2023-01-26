#include <vector>

using namespace std;

class Solution {
public:
    vector<vector<int>> spiralMatrix(int m, int n, ListNode* head) {
        vector<vector<int>> result(m, vector<int>(n, -1));
        int dx[4] = {0, 1, 0, -1};
        int dy[4] = {1, 0, -1, 0};
        // 范围
        int up = 0, down = m - 1, left = 0, right = n - 1;
        int d = 0;
        int x = 0, y = 0;
        ListNode *node = head;
        while(node != nullptr)
        {
            result[x][y] = node -> val;
            if(x + dx[d] == up && y + dy[d] == left)
            {
                d = 0;
                ++up;
                --down;
                ++left;
                --right;
            }
            else if(x + dx[d] < up || x + dx[d] > down || y + dy[d] < left || y + dy[d] > right)
            {
                d++;
            }
            x = x + dx[d];
            y = y + dy[d];
            node = node -> next;
        }
        return result;
    }
};
