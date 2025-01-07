#include "bits/stdc++.h"
using namespace std;

class Solution {
public:
    int mod = 1e9+7;
    
    int peopleAwareOfSecret(int n, int delay, int forget) {
        vector<long long> dp(n+1);
        dp[1] = 1;
        int ans = 0, share = 0;
        for(int i = 2; i <= n; i++){
            dp[i] = share = (share + dp[max(i- delay, 0)] - dp[max(i - forget, 0)] + mod) % mod;
        }
        for(int i = n - forget + 1; i <= n; i++){
            ans = (ans + dp[i]) % mod;
        }
        return ans % mod;
        
        
    }
};

int main(){
    Solution test;
    cout << test.peopleAwareOfSecret(684, 18, 496) << endl;
}