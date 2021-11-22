#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const ll INF = 1e18;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;
    vector<ll> ar(n + 2), pref(n + 2);
    vector<ll> mxPref(n + 2), mnPref(n + 2);
    vector<ll> mxSuf(n + 2), mnSuf(n + 2);

    for (int i = 1; i <= n; i++) {
        cin >> ar[i];
        pref[i] = pref[i - 1] + ar[i];
        mxPref[i] = max(mxPref[i - 1], pref[i]);
        mnPref[i] = min(mnPref[i - 1], pref[i]);
    }
    mxSuf[n] = mnSuf[n] = pref[n];
    for (int i = n - 1; i >= 0; i--) {
        mxSuf[i] = max(mxSuf[i + 1], pref[i]);
        mnSuf[i] = min(mnSuf[i + 1], pref[i]);
    }

    ll ans = -INF;
    for (int i = 1; i < n; i++) {
        ans = max(ans, abs(pref[i] * 2 - mnPref[i - 1] - mnSuf[i + 1]));
        ans = max(ans, abs(pref[i] * 2 - mxPref[i - 1] - mxSuf[i + 1]));
    }
    
    cout << ans << '\n';

    return 0;
}