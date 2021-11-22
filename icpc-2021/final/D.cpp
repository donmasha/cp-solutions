#include <bits/stdc++.h>

using namespace std;

const int K = 26;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    int n, m;
    cin >> n >> m;
    vector<string> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    int ans = 0;
    for (int j = 0; j < m; j++) {
        vector<int> cnt(K);
        for (int i = 0; i < n; i++) {
            cnt[a[i][j] - 'a']++;
        }
        int mx = *max_element(cnt.begin(), cnt.end());
        ans += n - mx;
    }
    cout << ans << '\n';

    return 0;
}