// prob911: Online Election

/*
 * https://leetcode-cn.com/problems/online-election/
 */

#include <map>
#include <set>
#include <vector>
#include <unordered_map>

using namespace std;

// 724ms
class TopVotedCandidate_2 {
public:
    TopVotedCandidate_2(vector<int>& persons, vector<int>& times) {
        int n = persons.size();
        winners = map<int, int>();
        ranking = set<Candidate>();
        mapping = unordered_map<int, set<Candidate>::iterator>();
        for(int i = 0; i < n; ++i)
        {
            int id = persons[i];
            int t = times[i];
            if(mapping.count(id) == 0)
            {
                Candidate cand(id, t, 1);
                ranking.insert(cand);
                mapping[id] = ranking.find(cand);
            }
            else
            {
                auto it = mapping[id];
                Candidate cand = *it;
                ranking.erase(ranking.find(cand));
                ++(cand.poll);
                cand.t = t;
                ranking.insert(cand);
                mapping[id] = ranking.find(cand);
            }
            winners[t] = ranking.begin() -> id;
        }
    }

    int q(int t) {
        // 调用方保证 t >= time[0]
        auto it = --winners.upper_bound(t);
        return it -> second;
    }

private:
    struct Candidate
    {
        int id;
        int t;
        int poll;
        Candidate(int id, int t=0, int poll=0):id(id),t(t),poll(poll){}
        bool operator<(const Candidate& c1) const
        {
            if(poll == c1.poll)
                return t > c1.t;
            return poll > c1.poll;
        }
    };

    map<int, int> winners; // start -> winners
    set<Candidate> ranking; // cand
    unordered_map<int, set<Candidate>::iterator> mapping; // id -> cand
};


// 612 ms
class TopVotedCandidate {
public:
    TopVotedCandidate(vector<int>& persons, vector<int>& times) {
        int n = persons.size();
        winners = map<int, int>();
        mapping = unordered_map<int, CandInfo>();
        for(int i = 0; i < n; ++i)
        {
            int id = persons[i];
            int t = times[i];
            if(mapping.count(id) == 0)
            {
                CandInfo cand_info(t, 1);
                mapping[id] = cand_info;
            }
            else
            {
                CandInfo &cand_info = mapping[id];
                ++(cand_info.poll);
                cand_info.t = t;
            }
            if(winners.empty())
            {
                winners[t] = id;
            }
            else
            {
                int prev_winner = winners.rbegin() -> second;
                CandInfo prev = mapping[prev_winner];
                CandInfo cur = mapping[id];
                if(prev.poll <= cur.poll)
                    winners[t] = id;
                else
                    winners[t] = prev_winner;
            }
        }
    }

    int q(int t) {
        // 调用方保证 t >= time[0]
        auto it = --winners.upper_bound(t);
        return it -> second;
    }

private:
    struct CandInfo
    {
        int t;
        int poll;
        CandInfo(int t=0, int poll=0):t(t),poll(poll){}
    };

    map<int, int> winners; // start -> winners
    unordered_map<int, CandInfo> mapping; // id -> cnt, t
};
