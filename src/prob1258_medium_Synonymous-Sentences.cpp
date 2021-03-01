// prob1258: Synonymous Sentences

/*
 * https://leetcode-cn.com/problems/synonymous-sentences/
 */

#include <unordered_map>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class UnionFindSet
{
public:
    UnionFindSet(){}
    UnionFindSet(int n)
    {
        _father.assign(n, 0);
        _rank.assign(n, 0);
        syns.assign(n, {});
        for(int i = 0; i < n; ++i)
            _father[i] = i;
        for(int i = 0; i < n; ++i)
            syns[i] = {i};
    }

    void merge(int id1, int id2)
    {
        id1 = _find(id1);
        id2 = _find(id2);
        if(id1 == id2)
            return;

        if(_rank[id1] < _rank[id2])
        {
            _father[id1] = id2;
            syns[id2].insert(syns[id2].end(), syns[id1].begin(), syns[id1].end());
        }
        else
        {
            _father[id2] = id1;
            syns[id1].insert(syns[id1].end(), syns[id2].begin(), syns[id2].end());
            if(_rank[id1] == _rank[id2])
                _rank[id1];
        }
    }

    vector<int> get_syns(int id)
    {
        return syns[_find(id)];
    }

private:
    vector<int> _father;
    vector<int> _rank;
    vector<vector<int>> syns;

    int _find(int id)
    {
        if(_father[id] == id)
            return id;
        return _father[id] = _find(_father[id]);
    }
};

struct Cmp
{
    vector<string> *words;
    Cmp(vector<string>* words):words(words){}
    Cmp(){}
    bool operator()(const int i1, const int i2) const
    {
        return (*words)[i1] < (*words)[i2];
    }
};

class Solution {
public:
    vector<string> generateSentences(vector<vector<string>>& synonyms, string text) {
        int id = 0;
        words = vector<string>();
        for(vector<string>& record: synonyms)
        {
            if(mapping.count(record[0]) == 0)
            {
                mapping[record[0]] = id++;
                words.emplace_back(record[0]);
            }
            if(mapping.count(record[1]) == 0)
            {
                mapping[record[1]] = id++;
                words.emplace_back(record[1]);
            }
        }
        cmp = Cmp(&words);
        unionfindset = UnionFindSet(id);
        for(vector<string>& record: synonyms)
        {
            unionfindset.merge(mapping[record[0]], mapping[record[1]]);
        }
        vector<string> result;
        string cand;
        dfs(text, 0, cand, result);
        return result;
    }

private:
    unordered_map<string, int> mapping; // word -> id
    vector<string> words;
    UnionFindSet unionfindset;
    Cmp cmp;

    void dfs(const string& text, int pos, string& cand, vector<string>& result)
    {
        int n = text.size();
        if(pos >= n)
        {
            cand.pop_back();
            result.emplace_back(cand);
            cand += ' ';
            return;
        }
        int t = text.find(' ', pos);
        int nxt;
        if(t == -1)
            nxt = n;
        else
            nxt = t;
        string w = text.substr(pos, nxt - pos);
        if(mapping.count(w) == 0)
        {
            cand += w;
            cand += ' ';
            dfs(text, nxt + 1, cand, result);
            cand.pop_back();
            cand.erase(cand.size() - w.size(), w.size());
            return;
        }
        vector<int> syn_ids = unionfindset.get_syns(mapping[w]);
        sort(syn_ids.begin(), syn_ids.end(), cmp);
        for(int id: syn_ids)
        {
            string &syn = words[id];
            cand += syn;
            cand += ' ';
            dfs(text, nxt + 1, cand, result);
            cand.pop_back();
            cand.erase(cand.size() - syn.size(), syn.size());
        }
    }
};
