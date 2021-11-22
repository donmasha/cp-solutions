#include <bits/stdc++.h>

using namespace std;
using pii = pair<int, int>;
using ll =  long long;

const int N = 1e5 + 10;
const int MX = 1e6 + 10;

int n;
int ar[N];
vector<pii> edges;

vector<int> fac[MX];
vector<pii> fedges[MX]; 

int par[N], sz[N];
int ans = 0;
vector<int> proc;
int find(int a){
    if (par[a] == a) return a;
    return par[a] = find(par[a]);
}
void make(int a, int b){
    proc.push_back(a);
    proc.push_back(b);
    a = find(a);
    b = find(b);
    if (a == b) return;
    if (sz[a] < sz[b]) swap(a, b);
    par[b] = a;
    sz[a] += sz[b];
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    cin >> n;
    for (int i=1;i<=n;i++){
        cin >> ar[i];
        if (ar[i] > 1) ans = 1;
    }
    for (int i=1;i<n;i++){
        int a, b;
        cin >> a >> b;
        edges.emplace_back(a, b);
    }
    for (int i=2;i<MX;i++){
        if (fac[i].size()) continue;
        for (int j=i;j<MX;j+=i){
            fac[j].push_back(i);
        }
    }
    for (auto& x : edges){
        int g = __gcd(ar[x.first], ar[x.second]);
        for (auto& y : fac[g]){
            fedges[y].emplace_back(x);
        }
    }
    for (int i=1;i<=n;i++){
        par[i] = i;
        sz[i] = 1;
    }
    for (int i=2;i<MX;i++){
        if (fedges[i].size()){
            for (auto& x : fedges[i]){
                make(x.first, x.second);
            }
            for (auto& y : proc){
                par[y] = y;
                ans = max(ans, sz[y]);
                sz[y] = 1;
            }
            proc.clear();
        }
    }
    cout << ans << '\n';

    return 0;
}