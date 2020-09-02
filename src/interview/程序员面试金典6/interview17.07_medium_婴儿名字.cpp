// interview17.07: 婴儿名字

/*
 * https://leetcode-cn.com/problems/baby-names-lcci/
 */

#include <vector>
#include <string>
#include <sstream>
#include <unordered_map>

using namespace std;

class UnionFindSet
{
public:
    UnionFindSet(const unordered_map<string, int>& mapping)
    {
        int n = mapping.size();
        _rank = vector<int>(n, 1);
        _w = vector<int>(n, -1);
        for(int i = 0; i < n; ++i)
            _w[i] = i;
        _father = vector<int>(n, -1);
        for(int i = 0; i < n; ++i)
            _father[i] = i;
        _mapping = vector<string>(n, "");
        for(const auto &item: mapping)
        {
            const string &name = item.first;
            int id = item.second;
            _mapping[id] = name;
        }
    }

    bool same(int a, int b)
    {
        return _find(a) == _find(b);
    }

    void merge(int a, int b)
    {
        int x = _find(a);
        int y = _find(b);
        if(x == y)
            return ;
        if(_rank[x] < _rank[y])
            _father[x] = y;
        else
        {
            _father[y] = x;
            if(_rank[x] == _rank[y])
                ++_rank[x];
        }
        if(_mapping[_w[x]] < _mapping[_w[y]])
            _w[y] = x;
        else
            _w[x] = y;
    }

    string query(int id)
    {
        int root = _find(id);
        return _mapping[_w[root]];
    }

private:
    vector<string> _mapping; // mapping[i] := 第 i 人的名字
    vector<int> _father;
    vector<int> _rank;
    vector<int> _w; // _w[root] := root 所属集合用的名字的 idx

    int _find(int x)
    {
        if(_father[x] == x)
            return x;
        return _father[x] = _find(_father[x]);
    }
};

class Solution {
public:
    vector<string> trulyMostPopular(vector<string>& names, vector<string>& synonyms) {
        unordered_map<string, int> mapping; // 有本质同名记录的名字对应的 id
        int id = 0;
        for(const string& item: synonyms)
        {
            // item 示例
            // "(Jon,John)"
            int n = item.size();
            int left = 1;
            int right = left + 1;
            while(right < n - 1 && item[right] != ',')
                ++right;
            string name1 = item.substr(left, right - left);
            string name2 = item.substr(right + 1, n - 1 - (right + 1));
            if(mapping.count(name1) == 0)
                mapping[name1] = id++;
            if(mapping.count(name2) == 0)
                mapping[name2] = id++;
        }
        unordered_map<string, int> records;
        UnionFindSet unionfindset(mapping);
        for(const string& item: synonyms)
        {
            // item 示例
            // "(Jon,John)"
            int n = item.size();
            int left = 1;
            int right = left + 1;
            while(right < n - 1 && item[right] != ',')
                ++right;
            string name1 = item.substr(left, right - left);
            string name2 = item.substr(right + 1, n - 1 - (right + 1));
            int id1 = mapping[name1];
            int id2 = mapping[name2];
            unionfindset.merge(id1, id2);
        }
        for(const string& item: names)
        {
            // item 示例
            // "John(15)"
            int n = item.size();
            int left = 0;
            int right = left + 1;
            while(right < n && item[right] != '(')
                ++right;
            string name = item.substr(left, right - left);
            string num = item.substr(right + 1, n - 1 - (right + 1));
            int cnt;
            stringstream ss;
            ss << num;
            ss >> cnt;
            if(mapping.count(name) == 0) // 无本质相同姓名记录
                records[name] += cnt;
            else
            {
                string base_name = unionfindset.query(mapping[name]);
                records[base_name] += cnt;
            }
        }
        vector<string> result;
        for(const auto &item: records)
        {
            const string &name = item.first;
            int cnt = item.second;
            result.push_back(name + '(' + to_string(cnt) + ')');
        }
        return result;
    }
};
