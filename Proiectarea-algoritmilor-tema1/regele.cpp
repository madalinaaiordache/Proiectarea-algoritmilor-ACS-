#include <bits/stdc++.h>

using namespace std;

ifstream f("regele.in");
ofstream g("regele.out");

// dp[i][j] = numarul maxim de negustori necesari pentru
// a activa j orase din primele i, ultimul oras activat fiind orasul i.

// smax[i] = numarul maxim de negustori pentru a
// activa i orase (maximul pe coloana i in matricea dp)

// mn[i][j] = max(dp[1][j], dp[2][j], ..., dp[i][j])

const int NMAX = 2e3;
int a[NMAX + 1], dp[NMAX + 1][NMAX + 1], smax[NMAX + 1], mx[NMAX + 1][NMAX + 1];

int main() {
    int n, k;
    f >> n;
    for (int i = 1; i <= n; i++) {
        f >> a[i];
    }
    a[0] = a[1];
    a[n + 1] = a[n];
    for (int i = 1; i <= n; i++) {
        dp[i][1] = a[i + 1] - a[i - 1];
        mx[i][1] = max(mx[i - 1][1], dp[i][1]);
    }
    for (int j = 2; j <= n; j++) {
        for (int i = j; i <= n; i++) {
            dp[i][j] = max(dp[i - 1][j - 1] + a[i + 1] - a[i],
                mx[i - 2][j - 1] + a[i + 1] - a[i - 1]);
            mx[i][j] = max(dp[i][j], mx[i - 1][j]);
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            smax[j] = max(smax[j], dp[i][j]);
        }
    }
    int q;
    f >> q;
    while (q--) {
        int x;
        f >> x;
        int sol = 0;
        int st = 1;
        int dr = n;
        // caut binar numarul maxim de orase care pot fi activate
        while (st <= dr) {
            int mid = (st + dr) / 2;
            if (smax[mid] <= x) {
                sol = max(mid, sol);
                st = mid + 1;
            } else {
                dr = mid - 1;
            }
        }
        g << sol << '\n';
    }
    return 0;
}
