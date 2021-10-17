#include<bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;

const ld PI = acos(-1);
const ld eps = 1e-9;

inline int sgn(ll x) { return (x == 0) ? 0 : (x < 0 ? -1 : 1); }

struct point {
    ll x, y;
    point(ll _x = 0, ll _y = 0) : x(_x), y(_y) {}
    point operator+ (const point& p) const { return point(x + p.x, y + p.y); }
    point operator- (const point& p) const { return point(x - p.x, y - p.y); }
    ll operator* (const point& p) const { return x * p.x + y * p.y; }
    ll operator% (const point& p) const { return x * p.y - y * p.x; }
    bool operator== (const point& p) const {
        return (x == p.x) && (y == p.y);
    }
    bool operator< (const point& p) const {
        return (y == p.y) ? (x < p.x) : (y < p.y);
    }
};

int ccw(point a, point b, point c) {
    return sgn((b - a) % (c - a));
}

void sortCircular(vector<pair<point, int>>& points) {
    vector<pair<point, int>> upper, lower;
    for (auto& e : points) {
        if (point() < e.first) upper.push_back(e);
        else lower.push_back(e);
    }
    auto cmp = [](pair<point, int> a, pair<point, int> b) {
        int dir = sgn(a.first % b.first);
        if (dir == 0) {
            return a.second < b.second;
        }
        return dir > 0;
    };
    sort(upper.begin(), upper.end(), cmp);
    sort(lower.begin(), lower.end(), cmp);
    for (int i = 0; i < upper.size(); i++) {
        points[i] = upper[i];
    }
    for (int i = 0; i < lower.size(); i++) {
        points[i + upper.size()] = lower[i];
    }
}

void solve() {
    int n;
    cin >> n;
    vector<point> pts;
    for (int i = 0; i < n; i++) {
        ll x, y;
        cin >> x >> y;
        pts.emplace_back(x, y);
    }
    ll ans = 0;
    for (int i = 0; i < n; i++) {
        vector<pair<point, int>> tmp;
        for (int j = 0; j < n; j++) {
            if (i == j) continue;
            if (pts[i] == pts[j]) continue;
            tmp.emplace_back(pts[j] - pts[i], j);
        }
        sortCircular(tmp);
        vector<ld> rad;
        for (int j = 0; j < tmp.size(); j++) {
            ld angle;
            if (tmp[j].first.x == 0) {
                if (tmp[j].first.y > 0) {
                    angle = 90;
                } else {
                    angle = 270;
                }
            } else {
                ld lol = atan(((ld)(tmp[j].first.y)) / (ld)(tmp[j].first.x));
                lol = lol * (((ld)180) / PI);
                bool kanan = tmp[j].first.x >= 0;
                bool atas = tmp[j].first.y >= 0;
                if (kanan && atas) {
                    lol = lol;
                } else if (!kanan && atas) {
                    lol = lol + ((ld)180);
                } else if (!kanan && !atas) {
                    lol = lol + ((ld)180);
                } else if (kanan && !atas) {
                    lol = lol + ((ld)360);
                }
                angle = lol;
            }
            rad.emplace_back(angle);
        }
        for (int j = 0; j < tmp.size(); j++) {
            rad.emplace_back(rad[j] +  ((ld)360));
        }
        for (int j = 0; j < tmp.size(); j++) {
            int t = lower_bound(rad.begin(), rad.end(), rad[j] + ((ld)90) - eps) - rad.begin();
            int cek = (t - j);
            ans += (cek - 1);
        }
    }
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