#include <bits/stdc++.h>

using namespace std;

ifstream f("walsh.in");
ofstream g("walsh.out");

int walsh(int x, int y, int sz, int value) {
    if (sz == 1) {
        return value;
    } else {
        sz /= 2;
        if (x <= sz && y <= sz) {
            return walsh(x, y, sz, value);
        } else {
            if (x <= sz & y > sz) {
                return walsh(x, y - sz, sz, value);
            } else {
                if (x > sz && y <= sz) {
                    return walsh(x - sz, y, sz, value);
                } else {
                    return walsh(x - sz, y - sz, sz, 1 - value);
                }
            }
        }
    }
}

int main() {
    int n, k;
    f >> n >> k;
    while (k--) {
        int x, y;
        f >> x >> y;
        g << walsh(x, y, n, 0) << '\n';
    }
    return 0;
}

