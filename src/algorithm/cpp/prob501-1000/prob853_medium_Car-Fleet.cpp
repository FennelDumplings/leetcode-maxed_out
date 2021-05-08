// prob853: Car Fleet

/*
 * https://leetcode-cn.com/problems/car-fleet/
 */

#include <vector>
#include <algorithm>

using namespace std;

struct Car
{
    int p, s;
    double t;
    Car(int p, int s, double t):p(p),s(s),t(t){}
};

struct Cmp
{
    bool operator()(const Car& c1, const Car& c2) const
    {
        return c1.p < c2.p;
    }
};

class Solution {
public:
    int carFleet(int target, vector<int>& position, vector<int>& speed) {
        int N = speed.size();
        if(N <= 1) return N;
        vector<Car> cars;
        for(int i = 0; i < N; ++i)
        {
            double t = (double)(target - position[i]) / speed[i];
            cars.push_back(Car(position[i], speed[i], t));
        }
        sort(cars.begin(), cars.end(), Cmp());
        int ans = 1;
        double prev = cars[N - 1].t;
        for(int i = N - 2; i >= 0; --i)
        {
            // times[i] <= prev 则为同一个车队
            // times[i] > prev 则为不同车队
            if(cars[i].t > prev)
            {
                prev = cars[i].t;
                ++ans;
            }
        }
        return ans;
    }
};
