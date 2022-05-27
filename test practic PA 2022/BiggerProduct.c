#include <bits/stdc++.h>
using namespace std;

const int NMAX = 150000;
const long double EPS = 1e-9;
long double a[NMAX + 1];

int main() {
    int n;
    cin >> n;
    long double sum = 0;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        sum += log(a[i]);
    }
    sort(a + 1, a + n + 1);
    int sol = 0;
    long double s = 0;
    for(int i = n; i >= 1; i--) {
        s += log(a[i]);
        if(s > sum - s || abs(2 * s - sum) < EPS) {
            sol = n - i + 1;
            break;
        }
    }
    cout << sol;
    return 0;
}