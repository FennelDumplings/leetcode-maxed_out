// prob631: Design Excel Sum Formula

/*
 * https://leetcode-cn.com/problems/design-excel-sum-formula/
 */

#include <vector>
#include <string>
#include <sstream>

using namespace std;

class Excel {
public:
    Excel(int H0, char W0) {
        this -> H = H0;
        this -> W = (W0 - 'A') + 1;
        A = vector<vector<int>>(H, vector<int>(W));
        D = vector<vector<int>>(H * W, vector<int>(H * W));
    }

    void set(int r, char c, int v) {
        int node_idx = get_node_idx(r - 1, c - 'A');
        for(int idx = 0; idx < H * W; ++idx)
            D[idx][node_idx] = 0;
        int diff = v - A[r - 1][c - 'A'];
        A[r - 1][c - 'A'] = v;
        dfs(node_idx, diff);
    }

    int get(int r, char c) {
        return A[r - 1][c - 'A'];
    }

    int sum(int r, char c, vector<string> strs) {
        int node_idx = get_node_idx(r - 1, c - 'A');
        for(int idx = 0; idx < H * W; ++idx)
            D[idx][node_idx] = 0;
        int ans = 0;
        for(const string& s: strs)
        {
            int part_it = s.find(":");
            if(part_it == (int)string::npos)
            {
                int w = s[0] - 'A';
                stringstream ss;
                ss << s.substr(1);
                int h;
                ss >> h;
                ans += A[h - 1][w];
                D[get_node_idx(h - 1, w)][node_idx] += 1;
            }
            else
            {
                int w_ul = s[0] - 'A';
                stringstream ss;
                ss << s.substr(1, part_it - 1);
                int h_ul;
                ss >> h_ul;
                int w_dr = s[part_it + 1] - 'A';
                ss.clear();
                ss << s.substr(part_it + 2);
                int h_dr;
                ss >> h_dr;
                for(int w = w_ul; w <= w_dr; ++w)
                    for(int h = h_ul; h <= h_dr; ++h)
                    {
                        ans += A[h - 1][w];
                        D[get_node_idx(h - 1, w)][node_idx] += 1;
                    }
            }
        }
        int diff = ans - A[r - 1][c - 'A'];
        A[r - 1][c - 'A'] = ans;
        dfs(node_idx, diff);
        return ans;
    }

private:
    vector<vector<int>> A;
    vector<vector<int>> D;
    int H, W;

    void dfs(int node, int diff)
    {
        for(int nxt = 0; nxt < H * W; ++nxt)
        {
            if(D[node][nxt] > 0)
            {
                int x, y;
                get_coord(nxt, x, y);
                A[x][y] += D[node][nxt] * diff;
                dfs(nxt, D[node][nxt] * diff);
            }
        }
    }

    int get_node_idx(int h, int w)
    {
        return h * W + w;
    }

    void get_coord(int idx, int& x, int& y)
    {
        x = idx / W;
        y = idx % W;
    }
};
