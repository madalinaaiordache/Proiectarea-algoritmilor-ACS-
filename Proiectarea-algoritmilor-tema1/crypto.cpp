#include <bits/stdc++.h>

using namespace std;

ifstream f("crypto.in");
ofstream g("crypto.out");

const int NMAX = 1e5;
const int MMAX = 10;
const long long MOD = 1e9 + 7;

long long dp[NMAX + 1][MMAX + 1];

// dp[i][j] = numarul de aparitii ale lui s[1...j] in k[1...j]

int main() {
    int n, m;
    f >> n >> m;
    string s, t;
    f >> s >> t;
    s = '#' + s;
    t = '#' + t;
    set<char> h;
    for (int i = 1; i <= m; i++) {
        h.insert(t[i]);
    }
    long long cnt = h.size();
    dp[0][0] = 1;
    for (int i = 1; i <= n; i++) {
        if (s[i] == '?') {
            dp[i][0] = (cnt * dp[i - 1][0]) % MOD;
        } else {
            dp[i][0] = dp[i - 1][0];
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= min(m, i); j++) {
            if (s[i] == '?') {
                dp[i][j] = (dp[i - 1][j - 1] +
                    (dp[i - 1][j] * cnt) % MOD) % MOD;
            } else {
                if (s[i] == t[j]) {
                     dp[i][j] = (dp[i - 1][j - 1] + dp[i - 1][j]) % MOD;
                } else {
                    dp[i][j] = dp[i - 1][j];
                }
            }
        }
    }
    g << dp[n][m] << '\n';
    return 0;
}
