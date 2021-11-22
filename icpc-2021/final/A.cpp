#pragma gcc optimize("O2")
#pragma gcc optimize("unroll-loops")

#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<int, int>;

const int N = 1e6 + 10;
const int M = 1e5 + 10;

const int LEN = 20;

int n, m;
// vector<int> skip;
vector<bool> take;

struct Node {
    int cnt = 0;
    Node* child[2];

    Node(){
        child[0] = child[1] = 0;
    }
    Node(int cnt) : cnt(cnt) {}
};
struct Trie {
    Node* head;
    Trie(){
        head = new Node();
    }

    void insert(int a){
        Node* cur = head;
        cur->cnt++;
        for (int i=LEN - 1;i>=0;i--){
            bool on = (a & (1 << i)) > 0;
            if (cur->child[on] == 0){
                cur->child[on] = new Node();
            }
            cur = cur->child[on];
            cur->cnt++;
        }
    }

    void erase(int a){
        Node* cur = head;
        cur->cnt--;
        for (int i=LEN - 1;i>=0;i--){
            bool on = (a & (1 << i)) > 0;
            cur = cur->child[on];
            cur->cnt--;
        }
    }

    ll calc(int a){
        Node* cur = head;
        ll ret = 0;
        for (int i=LEN - 1;i>=0;i--){
            bool on = (a & (1 << i)) > 0;
            if (on){
                if (cur->child[1]){
                    ret += cur->child[1]->cnt;
                }
                if (cur->child[0]){
                    cur = cur->child[0];
                } else break;
            } else{
                if (cur->child[0]){
                    cur = cur->child[0];
                } else break;
            }
        }
        return ret;
    }

    int get(int a){
        int cnt = 0;
        Node* cur = head;
        for (int i=LEN - 1;i>=0;i--){
            bool on = (a & (1 << i)) > 0;
            cur = cur->child[on];
        }
        return cur->cnt;
    }
};

Trie trie;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> m;
    take.assign(n + 1, 1);
    for (int i=0;i<m;i++){
        int a;
        cin >> a;
        // skip.push_back(a);
        if (a <= n) take[a] = 0;
    }
    for (int i=1;i<=n;i++){
        if (take[i]){
            trie.insert(i);
        }
    }
    ll ans = 0;
    for (int i=1;i<=n;i++){
        if (take[i]) trie.erase(i);
        ans += trie.calc(i);
    }
    cout << ans * 2 << '\n';

    return 0;
}