// prob990: Satisfiability of Equality Equations

/*
 * Given an array equations of strings that represent relationships between variables, each string equations[i] has
 * length 4 and takes one of two different forms: "a==b" or "a!=b".  Here, a and b are lowercase letters (not
 * necessarily different) that represent one-letter variable names.
 * Return true if and only if it is possible to assign integers to variable names so as to satisfy all the given equations.
 */

/*
 * Example 1:
 * Input: ["a==b","b!=a"]
 * Output: false
 * Explanation: If we assign say, a = 1 and b = 1, then the first equation is satisfied, but not the second.  There is no way to assign the variables to satisfy both equations.
 * Example 2:
 * Input: ["b==a","a==b"]
 * Output: true
 * Explanation: We could assign a = 1 and b = 1 to satisfy both equations.
 * Example 3:
 * Input: ["a==b","b==c","a==c"]
 * Output: true
 * Example 4:
 * Input: ["a==b","b!=c","c==a"]
 * Output: false
 * Example 5:
 * Input: ["c==c","b==d","x!=z"]
 * Output: true
 */

/*
 * Note:
 * 1 <= equations.length <= 500
 * equations[i].length == 4
 * equations[i][0] and equations[i][3] are lowercase letters
 * equations[i][1] is either '=' or '!'
 * equations[i][2] is '='
 */

#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

class UnionFindSet
{
public:
    UnionFindSet(int n)
    {
        _rank = vector<int>(n, 0);
        _father = vector<int>(n, 0);
        for(int i = 0; i < n; ++i)
            _father[i] = i;
    }

    bool same(int a, int b)
    {
        return _find(a) == _find(b);
    }

    void merge(int a, int b)
    {
        int x = _find(a);
        int y = _find(b);
        if(x == y) return;

        if(_rank[x] > _rank[y])
            _father[y] = x;
        else
        {
            _father[x] = y;
            if(_rank[x] == _rank[y])
                ++_rank[x];
        }
    }

private:
    vector<int> _rank, _father;

    int _find(int x)
    {
        if(_father[x] == x)
            return x;
        return _father[x] = _find(_father[x]);
    }
};

class Solution {
public:
    bool equationsPossible(vector<string>& equations) {
        UnionFindSet unionfindset(26);
        vector<string> tmp;
        for(const string& equation: equations)
        {
            char left_ch = equation[0], right_ch = equation[3];
            if(equation[1] == '=')
                unionfindset.merge(left_ch - 'a', right_ch - 'a');
            else
                tmp.push_back(equation);
        }
        for(const string& equation: tmp)
        {
            char left_ch = equation[0], right_ch = equation[3];
            if(unionfindset.same(left_ch - 'a', right_ch - 'a'))
                return false;
        }
        return true;
    }
};
