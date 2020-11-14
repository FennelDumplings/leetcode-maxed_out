// prob1357: Apply Discount Every n Orders

/*
 * https://leetcode-cn.com/problems/apply-discount-every-n-orders/
 */

#include <vector>
#include <unordered_map>

using namespace std;

class Cashier {
public:
    Cashier(int n, int discount, vector<int>& products, vector<int>& prices) {
        N = n;
        Discount = discount;
        for(int i = 0; i < (int)products.size(); ++i)
            mapping[products[i]] = prices[i];
        cnt = 0;
    }

    double getBill(vector<int> product, vector<int> amount) {
        double all = 0.0;
        for(int i = 0; i < (int)product.size(); ++i)
        {
            all += amount[i] * mapping[product[i]];
        }
        if(++cnt == N)
        {
            all = all - (Discount * all) / 100;
            cnt = 0;
        }
        return all;
    }

private:
    unordered_map<int, int> mapping; // id -> price
    int N;
    int cnt;
    int Discount;
};
