// prob1074: Number of Submatrices That Sum to Target

/*
 * https://leetcode-cn.com/problems/number-of-submatrices-that-sum-to-target/
 */

#include <vector>
#include <unordered_map>

using namespace std;

class Solution_2 {
public:
    int numSubmatrixSumTarget(vector<vector<int>>& matrix, int target) {
        if(matrix.empty()) return 0;
        int n = matrix.size();
        int m = matrix[0].size();

        sums2d = vector<vector<int> >(n + 1, vector<int>(m + 1, 0));
        for(int i = 1; i <= n; ++i)
            for(int j = 1; j <= m; ++j)
                sums2d[i][j] = sums2d[i][j - 1] + sums2d[i - 1][j]
                    - sums2d[i - 1][j - 1] + matrix[i - 1][j - 1];

        int ans = 0;
        for(int i = 0; i < n; ++i)
            for(int l = 0; l <= i; ++l)
            {
                vector<int> nums(m);
                for(int j = 0; j < m; ++j)
                    nums[j] = sum_region(l, j, i, j);
                ans += solve1d(nums, target);
            }
        return ans;
    }

private:
    vector<vector<int>> sums2d;
    unordered_map<int, int> mapping;

    int solve1d(const vector<int>& nums, const int target)
    {
        int m = nums.size();
        mapping.clear();
        mapping[0] = 1;
        int sum = 0;
        int ans = 0;
        for(int j = 0; j < m; ++j)
        {
            sum += nums[j];
            int gap = sum - target;
            ans += mapping[gap];
            ++mapping[sum];
        }
        return ans;
    }

    int sum_region(int row1, int col1, int row2, int col2)
    {
        // row1 <= row2, col1 <= col2
        return sums2d[row2 + 1][col2 + 1] - sums2d[row2 + 1][col1]
            - sums2d[row1][col2 + 1] + sums2d[row1][col1];
    }
};

#include <climits>

const int INF = 1e9;
typedef int hashType;

class CloseHashTable
{
private:
    struct Node
    {
        hashType data;
        int state;
        // 0: Empty  -1: deleted
        // >0: cnt/active
        Node()
        {
            state = 0;
        }
    };

    Node *arraytable;
    int sizetable;
    int (*key)(const hashType& x);
    const double A = 0.6180339887;

    static int defaultKey(const int &k)
    {
        return k;
    }

    int hash1(const hashType& x) const
    {
        return (key(x) + INF) % sizetable;
    }

    int hash2(const hashType& x) const
    {
        double d = (key(x) + INF) * A;
        return (int)(sizetable * (d - (int)d));
    }

public:
    CloseHashTable(int length=20011, int (*f)(const hashType &x)=defaultKey)
    {
        sizetable = length;
        arraytable = new Node[sizetable];
        key = f;
    }

    ~CloseHashTable()
    {
        delete[]arraytable;
    }

    int findx(const hashType &x) const;
    bool insertx(const hashType &x);
    bool removex(const hashType &x);
    void rehash();
};

int CloseHashTable::findx(const hashType &x) const
{
    int initPos = hash2(x);
    int pos = initPos;

    do
    {
        if(arraytable[pos].state == 0)
            return 0;
        if(arraytable[pos].state > 0 && key(arraytable[pos].data) == key(x))
            return arraytable[pos].state;
        pos = (pos + 1) % sizetable;
    }while(pos != initPos);

    return 0;
}

bool CloseHashTable::insertx(const hashType &x)
{
    int initPos = hash2(x);
    int pos = initPos;

    do{
        if(arraytable[pos].state <= 0)
        {
            arraytable[pos].data = x;
            arraytable[pos].state = 1;
            return true;
        }
        else if(arraytable[pos].state > 0 && key(arraytable[pos].data) == key(x))
        {
            // 无重集合改为直接返回 true
            ++arraytable[pos].state;
            return true;
        }
        pos = (pos + 1) % sizetable;
    }while(pos != initPos);

    return false;
}

bool CloseHashTable::removex(const hashType &x)
{
    int initPos = hash2(x);
    int pos = initPos;

    do
    {
        if(arraytable[pos].state == 0)
            return false;
        if(arraytable[pos].state > 0 && key(arraytable[pos].data) == key(x))
        {
            // 无重集合改为将 arraytable[pos].state 改为 -1 后返回
            --arraytable[pos].state;
            if(arraytable[pos].state == 0)
                arraytable[pos].state = -1;
            return true;
        }
        pos = (pos + 1) % sizetable;
    }while(pos != initPos);

    return false;
}

void CloseHashTable::rehash()
{
    Node *tmp = arraytable;
    arraytable = new Node[sizetable * 2];

    for(int i = 0; i < sizetable; ++i)
    {
        if(tmp[i].state > 0)
        {
            for(int j = 0; i < tmp[j].state; ++j)
                insertx(tmp[i].data);
        }
    }
    sizetable *= 2;

    delete [] tmp;
}


class Solution_3 {
public:
    int numSubmatrixSumTarget(vector<vector<int>>& matrix, int target) {
        if(matrix.empty()) return 0;
        int n = matrix.size();
        int m = matrix[0].size();

        sums2d = vector<vector<int> >(n + 1, vector<int>(m + 1, 0));
        for(int i = 1; i <= n; ++i)
            for(int j = 1; j <= m; ++j)
                sums2d[i][j] = sums2d[i][j - 1] + sums2d[i - 1][j]
                    - sums2d[i - 1][j - 1] + matrix[i - 1][j - 1];

        int ans = 0;
        for(int i = 0; i < n; ++i)
            for(int l = 0; l <= i; ++l)
            {
                vector<int> nums(m);
                for(int j = 0; j < m; ++j)
                    nums[j] = sum_region(l, j, i, j);
                ans += solve1d(nums, target);
            }
        return ans;
    }

private:
    vector<vector<int>> sums2d;

    int solve1d(const vector<int>& nums, const int target)
    {
        int m = nums.size();
        CloseHashTable mapping(613);
        mapping.insertx(0);
        int sum = 0;
        int ans = 0;
        for(int j = 0; j < m; ++j)
        {
            sum += nums[j];
            int gap = sum - target;
            ans += mapping.findx(gap);
            mapping.insertx(sum);
        }
        return ans;
    }

    int sum_region(int row1, int col1, int row2, int col2)
    {
        // row1 <= row2, col1 <= col2
        return sums2d[row2 + 1][col2 + 1] - sums2d[row2 + 1][col1]
            - sums2d[row1][col2 + 1] + sums2d[row1][col1];
    }
};

