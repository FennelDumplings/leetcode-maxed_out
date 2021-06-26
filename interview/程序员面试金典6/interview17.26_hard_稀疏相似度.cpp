// interview17.26: 稀疏相似度

/*
 * https://leetcode-cn.com/problems/sparse-similarity-lcci/
 */

#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <unordered_set>
#include <unordered_map>
#include <cstdio>

using namespace std;

class Solution {
public:
    vector<string> computeSimilarities(vector<vector<int>>& docs) {
        int n = docs.size();
        mapping = unordered_map<int, vector<int>>();
        intersection = vector<vector<int>>(n, vector<int>(n));
        for(int i = 0; i < n; ++i)
        {
            for(int a: docs[i])
                mapping[a].push_back(i);
        }
        for(const auto& word_info: mapping)
        {
            int m = (word_info.second).size();
            for(int i = 0; i < m - 1; ++i)
                for(int j = 0; j < m; ++j)
                {
                    int x = word_info.second[i];
                    int y = word_info.second[j];
                    ++intersection[x][y];
                }
        }
        vector<string> result;
        for(int i = 0; i < n - 1; ++i)
        {
            if(docs[i].empty())
                continue;
            for(int j = i + 1; j < n; ++j)
            {
                if(docs[j].empty())
                    continue;
                if(intersection[i][j] == 0)
                    continue;
                double sim = (double)intersection[i][j] / (docs[i].size() + docs[j].size() - intersection[i][j]);
                if(sim + 1e9 < 0.00005)
                    continue;
                // string res = "";
                // res += to_string(i) + ',' + to_string(j) + ": ";
                // string sim_str;
                // stringstream ss;
                // ss << std::fixed << std::setprecision(4);
                // ss << sim + 1e-9;
                // ss >> sim_str;
                // res += sim_str;
                char res[1024];
                sprintf(res, "%d,%d: %0.4lf", i, j, sim + 1e-9);
                result.push_back(res);
            }
        }
        return result;
    }

private:
    unordered_map<int, vector<int>> mapping;
    vector<vector<int>> intersection;
};

// 倒排索引
class Solution_2 {
public:
    vector<string> computeSimilarities(vector<vector<int>>& docs) {
        int n = docs.size();
        mapping = unordered_map<int, unordered_set<int>>();
        for(int i = 0; i < n; ++i)
        {
            for(int a: docs[i])
                mapping[a].insert(i);
        }
        vector<string> result;
        for(int i = 0; i < n - 1; ++i)
        {
            if(docs[i].empty())
                continue;
            for(int j = i + 1; j < n; ++j)
            {
                if(docs[j].empty())
                    continue;
                string res = "";
                res += to_string(i) + ',' + to_string(j) + ": ";
                double sim = get_sim(i, j, docs);
                string sim_str;
                stringstream ss;
                ss << std::fixed << std::setprecision(4);
                ss << sim + 1e-9;
                ss >> sim_str;
                if(sim_str != "0.0000")
                {
                    res += sim_str;
                    result.push_back(res);
                }
            }
        }
        return result;
    }

private:
    unordered_map<int, unordered_set<int>> mapping;

    double get_sim(int i, int j, const vector<vector<int>>& docs)
    {
        int union_size = docs[i].size() + docs[j].size(), intersection_size = 0;
        for(int word_i: docs[i])
        {
            if(mapping[word_i].count(j) > 0)
                ++intersection_size;
        }
        union_size -= intersection_size;
        return (double)intersection_size / union_size;
    }
};


// TLE
class Solution_1 {
public:
    vector<string> computeSimilarities(vector<vector<int>>& docs) {
        for(vector<int> &doc: docs)
            sort(doc.begin(), doc.end());
        int n = docs.size();
        vector<string> result;
        for(int i = 0; i < n - 1; ++i)
        {
            if(docs[i].empty())
                continue;
            for(int j = i + 1; j < n; ++j)
            {
                if(docs[j].empty())
                    continue;
                string res = "";
                res += to_string(i) + ',' + to_string(j) + ": ";
                double sim = get_sim(docs[i], docs[j]);
                string sim_str;
                stringstream ss;
                ss << std::fixed << std::setprecision(4);
                ss << sim + 1e-9;
                ss >> sim_str;
                if(sim_str != "0.0000")
                {
                    res += sim_str;
                    result.push_back(res);
                }
            }
        }
        return result;
    }

private:
    double get_sim(const vector<int>& doc1, const vector<int>& doc2)
    {
        vector<int> union_set, intersection_set;
        set_union(doc1.begin(), doc1.end(), doc2.begin(), doc2.end(), std::back_inserter(union_set));
        set_intersection(doc1.begin(), doc1.end(), doc2.begin(), doc2.end(), std::back_inserter(intersection_set));
        return (double)intersection_set.size() / union_set.size();
    }
};
