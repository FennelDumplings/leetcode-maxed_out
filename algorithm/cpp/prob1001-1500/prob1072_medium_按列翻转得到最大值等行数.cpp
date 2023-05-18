using ll = long long;
const int MOD = 1e9 + 7;
const int p = 13331;

struct Row
{
    vector<int> vec;
    Row(const vector<int>& row_data):vec(row_data)
    {
        int m = vec.size();
        if(vec[0] == 0)
        {
            for(int i = 0; i < m; ++i)
                vec[i] ^= 1;
        }
    }
    bool operator==(const Row& other) const
    {
        int m = vec.size();
        if(other.vec.size() != m)
            return false;
        for(int i = 0; i < m; ++i)
            if(other.vec[i] != vec[i])
                return false;
        return true;
    }
};

struct MyHash
{
    int operator()(const Row& row) const
    {
        int m = row.vec.size();
        int hash = 0;
        for(int i = 0; i < m; ++i)
        {
            hash = ((ll)hash * p) % MOD;
            hash = ((ll)hash + row.vec[i]) % MOD;
        }
        return hash;
    }
};

class Solution {
public:
    int maxEqualRowsAfterFlips(vector<vector<int>>& matrix) {
        unordered_map<Row, int, MyHash> mapping;
        int n = matrix.size();
        int m = matrix[0].size();
        for(int i = 0; i < n; ++i)
        {
            Row row(matrix[i]);
            mapping[row] += 1;
        }
        int ans = 1;
        for(auto record: mapping)
        {
            ans = max(ans, record.second);
        }
        return ans;
    }
};
