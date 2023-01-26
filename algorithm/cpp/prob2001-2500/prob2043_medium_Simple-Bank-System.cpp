#include <vector>

using namespace std;

using ll = long long;

class Bank {
public:
    Bank(vector<long long>& balance) {
        this -> n = balance.size();
        this -> balance = vector<ll>((this -> n) + 1);
        for(int i = 0; i < n; ++i)
            (this -> balance)[i + 1] = balance[i];
    }

    bool transfer(int account1, int account2, long long money) {
        if(account1 < 1 || account1 > n)
            return false;
        if(account2 < 1 || account2 > n)
            return false;
        if(balance[account1] < money)
            return false;
        balance[account1] -= money;
        balance[account2] += money;
        return true;
    }

    bool deposit(int account, long long money) {
        if(account < 1 || account > n)
            return false;
        balance[account] += money;
        return true;
    }

    bool withdraw(int account, long long money) {
        if(account < 1 || account > n)
            return false;
        if(balance[account] < money)
            return false;
        balance[account] -= money;
        return true;
    }

private:
    int n;
    vector<ll> balance;
};
