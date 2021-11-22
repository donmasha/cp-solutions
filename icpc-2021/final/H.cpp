#include <bits/stdc++.h>

using namespace std;

const int M = 13;
const int A = 26;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    int r, c;
    cin >> r >> c;
    vector<string> s(r);
    vector<int> cnt(A);
    for (int i = 0; i < r; i++) {
        cin >> s[i];
        for (auto ccc : s[i]) {
            if (ccc == '.') {
                continue;
            }
            cnt[ccc - 'a']++;
        }
    }
    int tot = 0;
    for (int i = 0; i < A; i++) {
        tot += cnt[i];
    }
    int halfTot = tot / 2;
    int mxmask = 1 << M;
    vector<pair<int, int>> leftHalf, rightHalf; //sum, mask
    {
        for (int i = 0; i < mxmask; i++) {
            int tmp = 0;
            for (int j = 0; j < M; j++) {
                if (i & (1 << j)) {
                    tmp += cnt[j];
                }
            }
            leftHalf.emplace_back(tmp, i);
        }
        sort(leftHalf.begin(), leftHalf.end());
    }
    {
        for (int i = 0; i < mxmask; i++) {
            int tmp = 0;
            for (int j = 0; j < M; j++) {
                if (i & (1 << j)) {
                    tmp += cnt[j + M];
                }
            }
            rightHalf.emplace_back(tmp, (i << M));
        }
        sort(rightHalf.begin(), rightHalf.end());
    }
    int lowHalf = 0;
    int maskMin = 0;
    for (int it = 0; it < 2; it++) {
        for (int i = 0; i < leftHalf.size(); i++) {
            int leftSum = leftHalf[i].first;
            int j = upper_bound(rightHalf.begin(), rightHalf.end(), make_pair(halfTot + 1 - leftSum, -1)) - rightHalf.begin();
            if (j == 0) {
                continue;
            }
            --j;
            int tmpSum = leftSum + rightHalf[j].first;
            if (tmpSum > lowHalf) {
                lowHalf = tmpSum;
                maskMin = (leftHalf[i].second | rightHalf[j].second);
            }
        }
        leftHalf.swap(rightHalf);
    }
    // cerr << "lowHalf: " << lowHalf << '\n';
    // cerr << "maskMin: " << (maskMin & (15)) << '\n';
    int hiHalf = tot - lowHalf;
    int mn = 1e9;
    pair<int, int> dim = {-1, -1};
    for (int rr = r; rr <= 2 * r + 1; rr++) {
        for (int cc = c; cc <= 2 * c + 1; cc++) {
            if (((rr * cc + 1) / 2) < hiHalf) {
                continue;
            }
            if (rr * cc < mn) {
                mn = rr * cc;
                dim = make_pair(rr, cc);
            }
        }
    }

    int r2 = dim.first;
    int c2 = dim.second;
    vector<vector<char>> snew(r2, vector<char>(c2, '.'));
    int x = 0, y = 0;
    int x1 = 0, y1 = 1;
    if (c2 == 1) {
        x1 = 1, y1 = 0;
    }
    for (int i = 0; i < 26; i++) {
        int tmp = 0;
        if (maskMin & (1 << i)) {
            while (tmp < cnt[i]) {
                snew[x1][y1] = (char) (i + 'a');
                if (y1 + 2 >= c2) {
                    x1++; y1 = ((x1 & 1) ? 0 : 1);
                    if (y1 >= c2) {
                        x1++; y1 = ((x1 & 1) ? 0 : 1);
                    }
                } else {
                    y1 += 2;
                }
                tmp++;
            }
        } else {
            while (tmp < cnt[i]) {
                snew[x][y] = (char) (i + 'a');
                if (y + 2 >= c2) {
                    x++; y = ((x & 1) ? 1 : 0);
                    if (y >= c2) {
                        x++; y = ((x & 1) ? 1 : 0);
                    }
                } else {
                    y += 2;
                }
                tmp++;
            }
        }
    }
    // cerr << "test\n";
    cout << r2 << ' ' << c2 << '\n';
    for (int i = 0; i < r2; i++) {
        for (int j = 0; j < c2; j++) {
            cout << snew[i][j];
        }
        cout << '\n';
    }

    return 0;
}