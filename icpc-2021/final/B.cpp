#pragma gcc optimize("O2")
#pragma gcc optimize("unroll-loops")

#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5;
const int L = 17;
const int INF = 2e9 + 5;

struct Lazy {
    int n;
    vector<int> t;
    vector<int> lazy;

    Lazy() {
        t.assign(4 * N, INF);
        lazy.assign(4 * N, INF);
    }

    void push(int v) {
        lazy[v << 1] = min(lazy[v << 1], lazy[v]);
        lazy[v << 1 | 1] = min(lazy[v << 1 | 1], lazy[v]);
        t[v << 1] = min(t[v << 1], lazy[v]);
        t[v << 1 | 1] = min(t[v << 1 | 1], lazy[v]);
        lazy[v] = INF;
    }

    void update(int v, int s, int e, int l, int r, int val) {
        if (e < l || s > r || l > r) {
            return;
        }
        if (l <= s && e <= r) {
            t[v] = min(t[v], val);
            lazy[v] = min(lazy[v], val);
            return;
        }
        push(v);
        int mid = (s + e) >> 1;
        update(v << 1, s, mid, l, r, val);
        update(v << 1 | 1, mid + 1, e, l, r, val);
        t[v] = min(t[v << 1], t[v << 1 | 1]);
    }

    int get(int v, int s, int e, int l, int r) {
        if (e < l || s > r || l > r) {
            return INF;
        }
        if (l <= s && e <= r) {
            return t[v];
        }
        push(v);
        int mid = (s + e) >> 1;
        int p1 = get(v << 1, s, mid, l, r);
        int p2 = get(v << 1 | 1, mid + 1, e, l, r);
        return min(p1, p2);
    }
};

int n, m;
int h[N];
vector<pair<int, int>> adj[N];
int tin[N], tout[N], tim;
int par[N], depth[N], heavy[N], head[N];
int up[N][L];
int maks[N][L];
int pos[N], id[N], curPos;
Lazy segtree;

int dfs_lca(int u, int p, int w) {
    up[u][0] = p;
    maks[u][0] = w;
    par[u] = p;
    depth[u] = (u == p ? 0 : depth[p] + 1);
    for (int i = 1; i < L; i++) {
        up[u][i] = up[up[u][i - 1]][i - 1];
        maks[u][i] = max(maks[up[u][i - 1]][i - 1], maks[u][i - 1]);
    }
    tin[u] = ++tim;
    int sz = 1;
    int max_sz = 0;
    for (auto [v, w] : adj[u]) {
        if (v == p) {
            continue;
        }
        int cur = dfs_lca(v, u, w);
        sz += cur;
        if (cur > max_sz) {
            max_sz = cur;
            heavy[u] = v;
        }
    }
    tout[u] = ++tim;
    return sz;
}

bool is_anc(int u, int v) {
    return (tin[u] <= tin[v] && tout[u] >= tout[v]);
}

int LCA(int u, int v) {
    if (is_anc(u, v)) {
        return u;
    }
    if (is_anc(v, u)) {
        return v;
    }
    for (int i = L - 1; i >= 0; i--) {
        if (!is_anc(up[u][i], v)) {
            u = up[u][i];
        }
    }
    return up[u][0];
}

int get_maks(int u, int v) {
    int w = LCA(u, v);
    int ret = 0;
    for (int x : {u, v}) {
        for (int i = L - 1; i >= 0; i--) {
            if (!is_anc(up[x][i], w)) {
                ret = max(ret, maks[x][i]);
                x = up[x][i];
            }
        }
        if (!is_anc(x, w)) ret = max(ret, maks[x][0]);
    }
    return ret;
}

void decompose(int u, int h) {
    head[u] = h;
    pos[u] = ++curPos;
    // cerr << "POS " << u << " => " << pos[u] << '\n';
    id[curPos] = u;
    if (heavy[u]) {
        decompose(heavy[u], h);
    }
    for (auto [v, w] : adj[u]) {
        if (v != par[u] && v != heavy[u]) {
            decompose(v, v);
        }
    }
}

void updatePath(int u, int v, int w) {
    int mx = max(w, get_maks(u, v));
    // cerr << u << " => " << v << " => " << w << " => " << mx << '\n';
    for ( ; head[u] != head[v]; u = par[head[u]]) {
        if (depth[head[u]] < depth[head[v]]) {
            swap(u, v);
        }
        segtree.update(1, 1, curPos, pos[head[u]], pos[u], mx);
        // cerr << "UPD-n " << pos[head[u]] << " to " << head[u] << '\n';
        // cerr << "UPD-p " << pos[head[u]] << " to " << head[u] << '\n';
    }
    if (depth[u] > depth[v]) {
        swap(u, v);
    }
    segtree.update(1, 1, curPos, pos[u], pos[v], mx);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> h[i];
    }
    vector<tuple<int, int, int>> edges(m);
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        int w = abs(h[u] - h[v]);
        edges[i - 1] = make_tuple(w, u, v);
    }
    // build the MST
    vector<int> par(n + 1);
    iota(par.begin(), par.end(), 0);
    function<int(int)> fpar = [&](int x) {
        if (par[x] == x) {
            return x;
        }
        return par[x] = fpar(par[x]);
    };
    auto merge = [&](int u, int v) {
        int pu = fpar(u);
        int pv = fpar(v);
        if (pu == pv) {
            return false;
        }
        par[pv] = pu;
        return true;
    };
    sort(edges.begin(), edges.end());
    vector<tuple<int, int, int>> rem;
    for (auto [w, u, v] : edges) {
        int pu = fpar(u);
        int pv = fpar(v);
        if (merge(pu, pv)) {
            adj[u].emplace_back(v, w);
            adj[v].emplace_back(u, w);
        } else {
            rem.emplace_back(u, v, w);
        }
    }
    dfs_lca(1, 1, 0);
    decompose(1, 1);
    for (auto [u, v, w] : rem) {
        updatePath(u, v, w);
    }
    for (int i = 1; i <= n; i++) {
        int res = segtree.get(1, 1, curPos, pos[i], pos[i]);
        if (res == INF) {
            res = -1;
        }
        cout << res << " \n"[i == n];
    }

    return 0;
}