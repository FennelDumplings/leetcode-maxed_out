// prob1244: Design A Leaderboard

/*
 * https://leetcode-cn.com/problems/design-a-leaderboard/
 */

#include <unordered_map>
#include <set>

using namespace std;

class Leaderboard {
public:
    Leaderboard() {
        scores = multiset<int>();
        players = unordered_map<int, int>();
    }

    void addScore(int playerId, int score) {
        if(players.count(playerId) == 0)
        {
            players[playerId] = score;
        }
        else
        {
            int s = players[playerId];
            auto it = scores.lower_bound(s);
            scores.erase(it);
            players[playerId] += score;
        }
        scores.insert(players[playerId]);
    }

    int top(int K) {
        auto it = scores.begin();
        int sum = 0;
        for(int i = 0; i < K; ++i)
        {
            sum += *it;
            ++it;
        }
        return sum;
    }

    void reset(int playerId) {
        int s = players[playerId];
        auto it = scores.lower_bound(s);
        scores.erase(it);
        players[playerId] = 0;
        scores.insert(0);
    }

private:
    multiset<int> scores;
    unordered_map<int, int> players;
};
