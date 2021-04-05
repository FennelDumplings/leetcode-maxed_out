
#include <unordered_set>
#include <unordered_map>
#include <vector>

using namespace std;

vector<int> get_primes(int n) {
    if(n < 2) return {};
    vector<bool> vec(n, true);
    vec[0] = false;
    vec[1] = false;
    for(int i = 2; i * i < n; ++i)
    {
        if(vec[i])
        {
            for(int j = i * i; j < n; j += i)
                vec[j] = false;
        }
    }
    vector<int> result;
    for(int i = 0; i < n; ++ i)
    {
        bool flag = vec[i];
        if(flag)
            result.push_back(i);
    }
    return result;
}

vector<int> get_prime_factor(int num, const vector<int>& primes) {
    // 大于 1 的质因数
   if(num <= 0) return {};
   if(num == 1) return {};
   vector<int> result;
   int m = primes.size();
   int i = 0;
   while(i < m && primes[i] <= num)
   {
       if(num % primes[i] == 0)
       {
           result.push_back(primes[i]);
           num /= primes[i];
       }
       else
           ++i;
   }
   return result;
}

class Solution {
public:
    int countDifferentSubsequenceGCDs(vector<int>& nums) {
        vector<int> primes = get_primes(2e5 + 1);
        unordered_set<int> setting;
        unordered_map<int, vector<int>> setting; // 因数 -> 含这个因数的数字列表
        for(int x: nums)
            setting.insert(x);
        for(int x: nums)
        {
            vector<int> factors = get_prime_factor(x, primes);
            for()
        }
    }
};

