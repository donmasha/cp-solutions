#include<bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;

const ll MOD = 1e9 + 7;

ll fpow(ll a, ll b) {
    ll ret = 1;
    while (b) {
        if (b & 1) { ret = (ret * a) % MOD; }
        a = (a * a) % MOD;
        b >>= 1;
    }
    return ret;
}

ll inv(ll a) {
    return fpow(a, MOD - 2);
}

void solve() {
    int n;
    cin >> n;
    vector<ll> a(8);
    vector<bool> hand(8);
    for (int i = 0; i < 8; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < 4; i++) {
        int b;
        cin >> b;
        --b;
        hand[b] = true;
    }
    vector<vector<ll>> dp1(n + 1, vector<ll>(2));
    vector<vector<ll>> dp2(n + 1, vector<ll>(2));
    ll inv4 = inv(4);
    dp1[0][0] = inv4;
    dp1[0][1] = 0;
    dp2[0][0] = 0;
    dp2[0][1] = inv4;
    
    for (int i = 1; i < n; i++) {
        dp1[i][0] = (dp1[i - 1][0] * 3 + dp1[i - 1][1]) % MOD;
        dp1[i][1] = (dp1[i - 1][0] + dp1[i - 1][1] * 3) % MOD;
        dp2[i][0] = (dp2[i - 1][0] * 3 + dp2[i - 1][1]) % MOD;
        dp2[i][1] = (dp2[i - 1][0] + dp2[i - 1][1] * 3) % MOD;
        dp1[i][0] = (dp1[i][0] * inv4) % MOD;
        dp1[i][1] = (dp1[i][1] * inv4) % MOD;
        dp2[i][0] = (dp2[i][0] * inv4) % MOD;
        dp2[i][1] = (dp2[i][1] * inv4) % MOD;
    }

    ll ans = 0;
    for (int i = 0; i < n; i++) {
        ll tmp = 0;
        for (int j = 0; j < 8; j++) {
            if (hand[j]) {
                tmp = (tmp + a[j] * dp1[i][0]) % MOD;
            } else {
                tmp = (tmp + a[j] * dp2[i][0]) % MOD;
            }
        }
        ans = (ans + tmp) % MOD;
    }
    ans %= MOD;
    if (ans < 0) ans += MOD;
    cout << ans << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int TC = 1;
    for(int i = 1; i <= TC; i++) {
        solve();
    }
  
    return 0;
}