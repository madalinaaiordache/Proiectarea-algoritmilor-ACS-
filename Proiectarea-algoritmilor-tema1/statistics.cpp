#include <bits/stdc++.h>

using namespace std;

ifstream f("statistics.in");
ofstream g("statistics.out");


const int NMAX = 1e5;
const int SIGMA = 26;
int cnt[NMAX + 1][SIGMA], d[NMAX + 1];
string s[NMAX + 1];

// cnt[i][j] = numarul de aparitii ale literei j in sirul s[i]

int main() {
    int n;
    f >> n;
    for (int i = 1; i <= n; i++) {
        f >> s[i];
        for (int j = 0; j < (int)s[i].size(); j++) {
            cnt[i][s[i][j] - 'a']++;
        }
    }
    int sol = -1;
    for (int c = 0; c < SIGMA; c++) {
        for (int i = 1; i <= n; i++) {
            d[i] = 2 * cnt[i][c] - s[i].size();
        }
        sort(d + 1, d + n + 1);
        int res = -1;
        int sum = 0;
        for (int i = n; i >= 1; i--) {
            sum += d[i];
            if (sum > 0) {
                res = n - i + 1;
            }
        }
        sol = max(sol, res);
    }
    g << sol << '\n';
    return 0;
}

