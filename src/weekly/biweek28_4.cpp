// 20200613
// 4

int a[309];
int dp[309][39];
int w[309][309];
int n,m;
int main(){
    while(cin>>n>>m){
        for(int i=1;i<=n;i++)scanf("%d",&houses[i]);

        memset(w,0,sizeof(w));

        for(int i=1;i<=n;i++){
            for(int j=i+1;j<=n;j++){
                dist[i][j]=dist[i][j-1]+houses[j]-houses[(i+j)/2];
            }
        }

        for(int i=1;i<=n;i++){
            dp[i][1]=dist[1][i];dp[i][i]=0;//一个邮局就是w[1][i]
        }

        for(int i=1;i<=n;i++){//末邮局位置
            for(int j=2;j<=min(m,i);j++){//邮局个数，当然比点的数量少
                dp[i][j] = INF;
                for(int k=j;k<=i-1;k++){//枚举可转移的位置，当然比邮局个数大
                    dp[i][j]=min(dp[i][j],dp[k][j-1]+dist[k+1][i]);
                }
            }
        }
        printf("%d\n",dp[n][m]);
    }
} 

#include <vector>
#include <climits>

using namespace std;

class Solution {
public:
    int minDistance(vector<int>& houses, int k) {
        int n = houses.size();
        vector<vector<int> > dist(n + 1, vector<int>(n + 1, 0));
        for(int i = 1; i <= n; ++i)
            for(int j = i + 1; j <= n; ++j)
                dist[i][j] = dist[i][j - 1] + houses[j] - houses[(i + j) / 2];
        vector<vector<int> > dp(n + 1, vector<int>(k + 1, INT_MAX));
        for(int i = 1; i <= n; ++i)
        {
            dp[i][1] = dist[1][i];
            if(i <= k)
                dp[i][i] = 0;
        }
        for(int i = 1;i <= n; ++i)
            for(int j = 2; j <= min(k, i); ++j)
            {
                dp[i][j] = INT_MAX;
                for(int l = j; l <= i - 1; ++l)
                    dp[i][j] = min(dp[i][j], dp[l][j - 1] + dist[l + 1][i]);
            }
        return dp[n][k];
    }
};
