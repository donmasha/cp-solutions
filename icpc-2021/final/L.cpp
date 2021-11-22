// too late
#pragma gcc optimize("O2")
#pragma gcc optimize("unroll-loops")

#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<int, int>;

const int N = 1e5 + 10;
const int INF = 2e9 + 10;

int n, k, d;
int h[N];
int t[N];

int rate[N];

struct Lazy {
    int n;
    vector<int> t;

    Lazy() {
        t.assign(4 * N, -INF);
    }

    void update(int v, int tl, int tr, int pos, int val){
        if (pos < tl || tr < pos) return;
        if (tl == tr && tl == pos){
            t[v] = val;
            return;
        }
        int tm = (tl + tr) / 2;
        update(v * 2, tl, tm, pos, val);
        update(v * 2 + 1, tm + 1, tr, pos, val);
        t[v] = max(t[v * 2], t[v * 2 + 1]);
    }

    int get(int v, int s, int e, int l, int r) {
        if (e < l || s > r || l > r) {
            return -INF;
        }
        if (l <= s && e <= r) {
            return t[v];
        }
        int mid = (s + e) >> 1;
        int p1 = get(v << 1, s, mid, l, r);
        int p2 = get(v << 1 | 1, mid + 1, e, l, r);
        return max(p1, p2);
    }
};

Lazy stree;
int dp[N];
set<pii> sdp[N];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> k >> d;
    for (int i=1;i<=n;i++){
        cin >> h[i];
    }
    for (int i=1;i<n;i++){
        cin >> t[i];
    }
    rate[0] = n / k + 1;
    for (int i=1;i<=n;i++){
        rate[i] = rate[i - 1];
        if ((i - 1) % k == 0) rate[i]--;
    }
    auto getnorm = [&](int id) -> int {
        return dp[id] - rate[id] * d;
    };
    auto getclass = [&](int id) -> int {
        return (id - 1) % k;
    };
    fill(dp, dp + N, -INF);
    priority_queue<pii, vector<pii>, greater<pii>> pq;

    auto set = [&](int id, int val) -> void {
        dp[id] = val;
        int a = getclass(id);
        int norm = getnorm(id);
        sdp[a].insert(make_pair(norm, id));
        pq.push(make_pair(id + t[id], id));
        stree.update(1, 0, k - 1, a, sdp[a].rbegin()->first);
    };
    auto del = [&](int id) -> void {
        int a = getclass(id);
        int norm = getnorm(id);
        sdp[a].erase(make_pair(norm, id));

        int nval = sdp[a].size() ? sdp[a].rbegin()->first : -INF;
        stree.update(1, 0, k - 1, a, nval);
    };
    set(1, h[1]);
    for (int i=2;i<=n;i++){
        while (!pq.empty() && pq.top().first < i){
            auto temp = pq.top();
            pq.pop();
            del(temp.second);
        }
        int a = getclass(i);
        int cur = stree.get(1, 0, k - 1, 0, a);
        int cur2 = stree.get(1, 0, k - 1, a + 1, k - 1);
        set(i, max(cur, cur2 + d) + rate[i] * d + h[i]);
    }
    cout << dp[n] << '\n';

    return 0;
}