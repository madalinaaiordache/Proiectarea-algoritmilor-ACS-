#include <bits/stdc++.h>

using namespace std;

ifstream f("prinel.in");
ofstream g("prinel.out");

const int NMAX = 1e5;
const int KMAX = 1e6;
int target[NMAX + 1], p[NMAX + 1], d[NMAX + 1];
bool can[NMAX + 1];
int dp[KMAX + 1];

// d[i] = numarul minim de pasi pentru a
// ajunge de la 1 la i folosind procedeul descris in enunt

// can[i] = true daca pot ajunge de la 1 la i prin
// procedeul din enunt, altfel false.

// dp[i] = numarul maxim de puncte ale unei submultimi pentru care se
// efectueaza i operatii de transformare
// pentru a ajunge la elementele din target

int main() {
    int n, k;
    f >> n >> k;
    int maxim = 0;
    for (int i = 1; i <= n; i++) {
        f >> target[i];
        maxim = max(maxim, target[i]);
    }
    for (int i = 1; i <= n; i++) {
        f >> p[i];
    }
    for (int i = 1; i <= maxim; i++) {
        d[i] = maxim;
    }
    can[1] = true;
    d[1] = 0;
    for (int i = 1; i <= maxim; i++) {
        if (can[i]) {
            for (int j = 1; j * j <= i; j++) {
                if (i % j == 0) {
                    if (i + j <= maxim) {
                        can[i + j] = true;
                        d[i + j] = min(d[i + j], d[i] + 1);
                    }
                    if (i + i / j <= maxim) {
                        can[i + i / j] = true;
                        d[i + i / j] = min(d[i + i / j], d[i] + 1);
                    }
                }
            }
        }
    }
    // rucsac
    int smax = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = smax; j >= 1; j--) {
            if (dp[j] && j + d[target[i]] <= k) {
                dp[j + d[target[i]]] = max(dp[j + d[target[i]]], dp[j] + p[i]);
                smax = max(smax, j + d[target[i]]);
            }
        }
        if (d[target[i]] <= k) {
            dp[d[target[i]]] = max(dp[d[target[i]]], dp[0] + p[i]);
            smax = max(smax, d[target[i]]);
        }
    }
    int sol = 0;
    for (int i = 0; i <= k; i++) {
        sol = max(sol, dp[i]);
    }
    g << sol;
    return 0;
}
