// prob1333: Filter Restaurants by Vegan-Friendly, Price and Distance

/*
 * https://leetcode-cn.com/problems/filter-restaurants-by-vegan-friendly-price-and-distance/
 */

#include <algorithm>
#include <vector>

using namespace std;

struct Restaurant
{
    int id, rate;
    Restaurant(int id, int rate):id(id),rate(rate){}
};

struct Cmp
{
    bool operator()(const Restaurant& r1, const Restaurant& r2) const
    {
        if(r1.rate == r2.rate)
            return r1.id > r2.id;
        return r1.rate > r2.rate;
    }
};

class Solution {
public:
    vector<int> filterRestaurants(vector<vector<int>>& restaurants, int veganFriendly, int maxPrice, int maxDistance) {
        vector<Restaurant> vec;
        for(const vector<int> &item: restaurants)
        {
            if(veganFriendly == 1 && item[2] == 0)
                continue;
            if(item[3] > maxPrice)
                continue;
            if(item[4] > maxDistance)
                continue;
            vec.emplace_back(item[0], item[1]);
        }
        sort(vec.begin(), vec.end(), Cmp());
        int m = vec.size();
        vector<int> result(m);
        for(int i = 0; i < m; ++i)
            result[i] = vec[i].id;
        return result;
    }
};
