#include <bits/stdc++.h>
using namespace std;

ifstream f("curatare.in");
ofstream g("curatare.out");

const int NMAX = 1000;
const int RMAX = 4;
const int SMAX = 4;

int n, m;
int dist[SMAX + 1][NMAX + 1][NMAX + 1];

int a[NMAX + 1][NMAX + 1];
vector<pair<int, int>> r, s;
int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};
vector<int> p;
int v[SMAX + 1];

bool inside(int x, int y) {
    return x >= 1 && x <= n && y >= 1 && y <= m;
}

int sol = NMAX * NMAX;

// calculam distanta minima de la fiecare zona murdara
// catre orice pozitie libera din matrice
void bfs(int idr, int x, int y) {
    queue<pair<int, int>> q;
    dist[idr][x][y] = 1;
    q.push({x, y});
    while (!q.empty()) {
        int px = q.front().first;
        int py = q.front().second;
        q.pop();
        for (int i = 0; i < 4; i++) {
            int nx = px + dx[i];
            int ny = py + dy[i];
            if (inside(nx, ny) && !a[nx][ny] && !dist[idr][nx][ny]) {
                dist[idr][nx][ny] = 1 + dist[idr][px][py];
                q.push({nx, ny});
            }
        }
    }
}

// generam toate configuratiile posibile de curatare
void bkt(int k) {
    if (k == s.size()) {
        int sum[RMAX + 1] = {0};
        vector<pair<int, int>> posr = r;
        int mx = 0;
        for (int i = 0; i < (int)s.size(); i++) {
            sum[v[i]] += dist[p[i]][posr[v[i]].first][posr[v[i]].second] - 1;
            posr[v[i]] = s[p[i]];
            mx = max(mx, sum[v[i]]);
        }
        sol = min(sol, mx);

    } else {
        for (int i = 0; i < (int)r.size(); i++) {
            v[k] = i;
            bkt(k + 1);
        }
    }
}


int main() {
    f >> n >> m;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            char c;
            f >> c;
            if (c == 'X') {
                a[i][j] = -1;
            }
            if (c == 'R') {
                r.push_back({i, j});
            }
            if (c == 'S') {
                s.push_back({i, j});
            }
        }
    }
    for (int i = 0; i < (int)s.size(); i++) {
        p.push_back(i);
        bfs(i, s[i].first, s[i].second);
    }
    do {
        bkt(0);
    } while (next_permutation(p.begin(), p.end()));
    g << sol;
    return 0;
}
