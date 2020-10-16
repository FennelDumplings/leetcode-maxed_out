// prob950: Reveal Cards In Increasing Order

/*
 * https://leetcode-cn.com/problems/reveal-cards-in-increasing-order/
 */

#include <vector>
#include <algorithm>
#include <list>

using namespace std;

class Solution {
public:
    vector<int> deckRevealedIncreasing(vector<int>& deck) {
        int n = deck.size();
        sort(deck.begin(), deck.end());
        list<int> start;
        for(int i = n - 1; i >= 0; --i)
        {
            start.push_front(deck[i]);
            if(i > 0)
            {
                start.push_front(start.back());
                start.pop_back();
            }
        }
        return vector<int>(start.begin(), start.end());
    }
};
