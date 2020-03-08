// prob957: Prison Cells After N Days

/*
 * There are 8 prison cells in a row, and each cell is either occupied or vacant.
 * Each day, whether the cell is occupied or vacant changes according to the following rules:
 * If a cell has two adjacent neighbors that are both occupied or both vacant, then the cell becomes occupied.
 * Otherwise, it becomes vacant.
 * (Note that because the prison is a row, the first and the last cells in the row can't have two adjacent neighbors.)
 * We describe the current state of the prison in the following way: cells[i] == 1 if the i-th cell is occupied, else cells[i] == 0.
 * Given the initial state of the prison, return the state of the prison after N days (and N such changes described above.)
 */

/*
 * Example 1:
 *
 * Input: intervals = [[1,3],[6,9]], newInterval = [2,5]
 * Output: [[1,5],[6,9]]
 * Example 2:
 *
 * Input: intervals = [[1,2],[3,5],[6,7],[8,10],[12,16]], newInterval = [4,8]
 * Output: [[1,2],[3,10],[12,16]]
 * Explanation: Because the new interval [4,8] overlaps with [3,5],[6,7],[8,10].
 */

#include <vector>

using namespace std;

// 找循环节
class Solution {
public:
    vector<int> prisonAfterNDays(vector<int>& cells, int N) {
        int m = cells.size();
        vector<int> vis(1 << m, -1);

        vis[getHash(cells)] = 0;

        for (int i = 1; i <= N; i++) {
            cells = nextDay(cells);
            int h = getHash(cells);
            if (vis[h] != -1) {
                int l = i - vis[h];
                i = N - (N - vis[h]) % l; // 跳过循环节
            }
            vis[h] = i;
        }
        return cells;
    }

private:
    vector<int> nextDay(const vector<int>& cells) {
        int m = cells.size();
        vector<int> ans(m, 0);
        for (int i = 1; i < m - 1; i++)
            ans[i] = 1 - (cells[i - 1] ^ cells[i + 1]);
        return ans;
    }

    int getHash(const vector<int>& cells) {
        int m = cells.size(), tot = 0;
        for (int i = 0; i < m; i++)
            if (cells[i])
                tot += 1 << i;
        return tot;
    }
};

// 矩阵快速幂
// 找到递推式

class Matrix {
public:
    Matrix(int m){
        M = m;
        mat = vector<vector<int> >(M, vector<int>(M, 0));
    }

    void assign(int i, int j, int val)
    {
        mat[i][j] = val;
    }

    int get(int i, int j)
    {
        return mat[i][j];
    }

    void init()
    {
        for(int i = 0; i < M; ++i)
            for(int j = 0; j < M; ++j)
                mat[i][j] = 0;
        for(int i = 0; i < M; ++i)
            mat[i][i] = 1;
    }

    Matrix operator*(const Matrix& matrix) const
    {
        Matrix ans(M);
        for(int i = 0; i < M; ++i)
            for(int j = 0; j < M; ++j)
                for(int k = 0; k < M; ++k)
                    ans.mat[i][j] = (ans.mat[i][j] + (ll)mat[i][k] * matrix.mat[k][j]) % MOD;
        return ans;
    }

    Matrix operator^(int n) const
    {
        Matrix ans(M);
        ans.init();
        Matrix A = *this; // 拷贝出来用于自乘
        while(n)
        {
            if(n & 1) ans = ans * A;
            A = A * A;
            n >>= 1;
        }
        return ans;
    }

    void operator=(const Matrix& matrix)
    {
        for(int i = 0; i < M; ++i)
            for(int j = 0; j < M; ++j)
                mat[i][j] = matrix.mat[i][j];
    }

private:
    vector<vector<int> > mat;
    int M;
    const int MOD = 2;
    using ll = long long;
};

// m 较大时候适用
class Solution_2 {
public:
    vector<int> prisonAfterNDays(vector<int>& cells, int N) {
        int m = cells.size();
        Matrix mat(m + 1);
        for(int i = 1; i < m - 1; ++i)
        {
            mat.assign(i, i - 1, 1);
            mat.assign(i, i + 1, 1);
            mat.assign(i, m, 1);
        }
        mat.assign(m, m, 1);
        Matrix mat_power = mat ^ N;
        vector<int> ans(m + 1, 0);
        cells.push_back(1);
        for(int i = 0; i <= m; ++i)
        {
            int result = 0;
            for(int j = 0; j <= m; ++j)
            {
                result = (result + mat_power.get(i, j) * cells[j]) % 2;
            }
            ans[i] = result;
        }
        ans.pop_back();
        return ans;
    }
};
