
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

using ll = long long;

struct Fraction
{
    ll n, m; // n/m
    Fraction(int n, int m):n(n),m(m){}
    void flip() // 取倒数
    {
        swap(this -> n, this -> m);
    }
    void add(const Fraction x)
    {
        this -> m *= x.m;
        this -> n = x.n * (this -> m) + x.m * (this -> n);
        ll gcd_ = gcd<ll>(this -> m, this -> n);
        this -> m /= gcd_;
        this -> n /= gcd_;
    }
};

class Solution {
public:
    vector<int> fraction(vector<int>& cont) {
        Fraction ans = _fraction(cont, 0);
        return vector<int>{int(ans.n), int(ans.m)};
    }

private:
    Fraction _fraction(const vector<int>& cont, int i)
    {
        int n = cont.size();
        if(i == n - 1)
            return Fraction(cont[i], 1);
        Fraction sub_ans = _fraction(cont, i + 1);
        sub_ans.flip();
        sub_ans.add(Fraction(cont[i], 1));
        return sub_ans;
    }
};
