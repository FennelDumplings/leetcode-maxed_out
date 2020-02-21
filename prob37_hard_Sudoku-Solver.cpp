// prob37: Sudoku Solver

/*
 * Write a program to solve a Sudoku puzzle by filling the empty cells.
 * A sudoku solution must satisfy all of the following rules:
 * Each of the digits 1-9 must occur exactly once in each row.
 * Each of the digits 1-9 must occur exactly once in each column.
 * Each of the the digits 1-9 must occur exactly once in each of the 9 3x3 sub-boxes of the grid.
 * Empty cells are indicated by the character '.'.
 */

/*
 * Note:
 * The given board contain only digits 1-9 and the character '.'.
 * You may assume that the given Sudoku puzzle will have a single unique solution.
 * The given board size is always 9x9.
 */

#include <vector>
#include <unordered_set>
#include <iostream>

using namespace std;

class Solution {
public:
    void solveSudoku(vector<vector<char>>& board) {
        _solveSudoku(board, 0);
    }

private:
    bool _solveSudoku(vector<vector<char>>& board, int pos)
    {
        int i = pos / 9;
        int j = pos % 9;
        if(board[i][j] != '.')
        {
            if(pos == 80)
                return true;
            else
                return _solveSudoku(board, pos + 1);
        }
        char nums[9] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
        for(char item : nums)
        {
            if(check(board, i, j, item))
            {
                board[i][j] = item;
                if(pos == 80) return true;
                bool solved = _solveSudoku(board, pos + 1);
                if(solved) return true;
                board[i][j] = '.';
            }
        }
        return false;
    }

    // 对于当前点 (i, j)， 输入一种数字后，判断状态是否合法
    bool check(vector<vector<char> >& board, int i, int j, char num)
    {
        if(check_row(board, i, num) && check_col(board, j, num) && check_block(board, i, j, num))
            return true;
        return false;
    }

    bool check_row(vector<vector<char> >& board, int i, char num)
    {
        for(int j = 0; j < 9; ++j)
            if(board[i][j] == num)
                return false;
        return true;
    }

    bool check_col(vector<vector<char> >& board, int j, char num)
    {
        for(int i = 0; i < 9; ++i)
            if(board[i][j] == num)
                return false;
        return true;
    }

    bool check_block(vector<vector<char> >& board, int i, int j, char num)
    {
        pair<int, int> block_begin = _get_block_topleft(i, j);
        for(int i = block_begin.first; i < block_begin.first + 3; ++i)
            for(int j = block_begin.second; j < block_begin.second + 3; ++j)
                if(board[i][j] == num)
                    return false;
        return true;
    }

    pair<int, int> _get_block_topleft(int i, int j)
    {
        if(i <= 2)
        {
            if(j <= 2)
                return pair<int, int>(0, 0);
            else if(j >= 3 && j <= 5)
                return pair<int, int>(0, 3);
            else
                return pair<int, int>(0, 6);
        }
        else if(i >= 3 && i <= 5)
        {
            if(j <= 2)
                return pair<int, int>(3, 0);
            else if(j >= 3 && j <= 5)
                return pair<int, int>(3, 3);
            else
                return pair<int, int>(3, 6);
        }
        else
        {
            if(j <= 2)
                return pair<int, int>(6, 0);
            else if(j >= 3 && j <= 5)
                return pair<int, int>(6, 3);
            else
                return pair<int, int>(6, 6);
        }
    }
};

// 哈希表的键在 0-9 之间，可以用 vector<int> 取代哈希表
class Solution_2 {
public:
    void solveSudoku(vector<vector<char>>& board) {
        row_state = vector<vector<bool> >(9, vector<bool>(9, false)); // row_state[i][j] 标识表示第 i 行的 j 有没有选
        col_state = vector<vector<bool> >(9, vector<bool>(9, false));
        block_state = vector<vector<bool> >(9, vector<bool>(9, false));
        for(int i = 0; i < 9; ++i)
            for(int j = 0; j < 9; ++j)
                if(board[i][j] != '.')
                {
                    row_state[i][int(board[i][j] - '0' - 1)] = true;
                    col_state[j][int(board[i][j] - '0' - 1)] = true;
                    block_state[_get_block_id(i, j)][int(board[i][j] - '0' - 1)] = true;
                }
        _solveSudoku(board, 0);
    }

private:
    vector<vector<bool> > row_state;
    vector<vector<bool> > col_state;
    vector<vector<bool> > block_state;

    bool _solveSudoku(vector<vector<char>>& board, int pos)
    {
        int i = pos / 9;
        int j = pos % 9;
        if(board[i][j] != '.')
        {
            if(pos == 80)
                return true;
            else
                return _solveSudoku(board, pos + 1);
        }
        char nums[9] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
        for(int it = 0; it < 9; ++it)
        {
            char item = nums[it];
            if(check(i, j, item))
            {
                board[i][j] = item;
                update(i, j, item);
                if(pos == 80) return true;
                bool solved = _solveSudoku(board, pos + 1);
                if(solved) return true;
                rollback(i, j, item);
                board[i][j] = '.';
            }
        }
        return false;
    }

    void update(int i, int j, char item)
    {
        row_state[i][int(item - '0' - 1)] = true;
        col_state[j][int(item - '0' - 1)] = true;
        block_state[_get_block_id(i, j)][int(item - '0' - 1)] = true;
    }

    void rollback(int i, int j, char item)
    {
        row_state[i][int(item - '0' - 1)] = false;
        col_state[j][int(item - '0' - 1)] = false;
        block_state[_get_block_id(i, j)][int(item - '0' - 1)] = false;
    }


    // 对于当前点 (i, j)， 输入一种数字后，判断状态是否合法
    bool check(int i, int j, char item)
    {
        return !row_state[i][int(item - '0' - 1)]
            && !col_state[j][item - '0' - 1]
            && !block_state[_get_block_id(i, j)][int(item - '0' - 1)];
    }

    int _get_block_id(int i, int j)
    {
        if(i <= 2)
        {
            if(j <= 2)
                return 0;
            else if(j >= 3 && j <= 5)
                return 1;
            else
                return 2;
        }
        else if(i >= 3 && i <= 5)
        {
            if(j <= 2)
                return 3;
            else if(j >= 3 && j <= 5)
                return 4;
            else
                return 5;
        }
        else
        {
            if(j <= 2)
                return 6;
            else if(j >= 3 && j <= 5)
                return 7;
            else
                return 8;
        }
    }
};


// 剪枝加位运算
// https://leetcode-cn.com/problems/sudoku-solver/solution/jie-shu-du-1ms100-dfsjian-zhi-wei-yun-suan-by-ri-m/
// 剪枝条件:我们应该选择的格子（'.'）在一行、一列和一个九宫格中可选数字最少的格子开始填数字。
// 对于每行、每列和每个9宫格都可以用一个9位的2进制数字来标识该行（列，9宫格）那些数字可以填。
//     用1表示可填0表示不可填
//     如例题中第一行 ：["5","3",".",".","7",".",".",".","."]
//     第一行中 有数字 5 3 7
//                     下标    8  7  6  5  4  3  2  1  0
//                 二进制数    1  1  0  1  0  1  0  1  1
//     因为5 3 7 已经有了，所以第一行1 2 4 6 8 9可填
//     一共有9行所以用9个int表示行row[9],同理9列col[9],9个9宫格cell[3][3]
//     Java
class Solution_optim {
    final int N = 9;
    int[] row = new int [N], col = new int [N];
    //ones数组表示0~2^9 - 1的整数中二进制表示中1的个数:如ones[7] = 3 ones[8] = 1
    //map数组表示2的整数次幂中二进制1所在位置（从0开始） 如 map[1] = 0,map[2] = 1, map[4] = 2
    int[] ones = new int[1 << N], map = new int[1 << N];
    int[][] cell = new int[3][3];
    public void solveSudoku(char[][] board) {
        init();
        int cnt = fill_state(board);
        dfs(cnt, board);
    }
    void init(){
        for(int i = 0; i < N; i++) row[i] = col[i] = (1 << N) - 1;
        for(int i = 0; i < 3; i++)
            for(int j = 0; j < 3; j++)
                cell[i][j] = (1 << N) - 1;
        //以上2个循环把数组的数初始化为二进制表示9个1，即一开始所以格子都可填
        for(int i = 0; i < N; i++) map[1 << i] = i;
        //统计0~2^9 - 1的整数中二进制表示中1的个数
        for(int i = 0; i < 1 << N; i++){
            int n = 0;
            for(int j = i; j != 0; j ^= lowBit(j)) n++;
            ones[i] = n;
        }
    }
    int fill_state(char[][] board){
        int cnt = 0;    //统计board数组空格('.')的个数
        for(int i = 0; i < N; i++){
            for(int j = 0; j < N; j++){
                if(board[i][j] != '.'){
                    int t = board[i][j] - '1';
                    //数独中 i,j位置为数组下标，修改row col cell数组中状态
                    change_state(i, j, t);
                }else cnt++;
            }
        }
        return cnt;
    }
    boolean dfs(int cnt, char[][] board){
        if(cnt == 0) return true;
        int min = 10, x = 0, y = 0;
        //剪枝，即找出当前所以空格可填数字个数最少的位置 记为x y
        for(int i = 0; i < N; i++){
            for(int j = 0; j < N; j++){
                if(board[i][j] == '.'){
                    int k = ones[get(i, j)];
                    if(k < min){
                        min = k;
                        x = i;
                        y = j;
                    }
                }
            }
        }
        //遍历当前 x y所有可选数字
        for(int i = get(x, y); i != 0; i ^= lowBit(i)){
            int t = map[lowBit(i)];

            change_state(x, y, t);
            board[x][y] = (char)('1' + t);

            if(dfs(cnt - 1, board)) return true;

            //恢复现场
            change_state(x, y, t);
            board[x][y] = '.';
        }
        return false;
    }
    void change_state(int x, int y, int t){
        row[x] ^= 1 << t;
        col[y] ^= 1 << t;
        cell[x / 3][y / 3] ^= 1 << t;
    }
    //对维护数组x行,y列的3个集合(行、列、九宫格)进行&运算
    //就可以获得可选数字的集合(因为我们用1标识可填数字)
    int get(int x, int y){
        return row[x] & col[y] & cell[x / 3][y / 3];
    }
    int lowBit(int x){
        return -x & x;
    }
}
