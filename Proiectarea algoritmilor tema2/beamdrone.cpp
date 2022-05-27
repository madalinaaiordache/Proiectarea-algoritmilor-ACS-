#include <bits/stdc++.h>
using namespace std;

ifstream f("beamdrone.in");
ofstream g("beamdrone.out");

const int INF = 1e8;
const int NMAX = 1000;
bool a[NMAX + 1][NMAX + 1];
int dist[2][NMAX + 1][NMAX + 1];
int n, m;

const int dx[][2] = {{-1, 1}, {0, 0}};
const int dy[][2] = {{0, 0}, {-1, 1}};

bool inside(int x, int y) {
    return x >= 1 && x <= n && y >= 1 && y <= m;
}

int main() {
    f >> n >> m;
    int xs, ys, xe, ye;
    f >> xs >> ys >> xe >> ye;
    xs++;
    ys++;
    xe++;
    ye++;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            char c;
            f >> c;
            if (c == '.') {
                a[i][j] = true;
            }
            dist[0][i][j] = dist[1][i][j] = INF;
        }
    }
    // 0-1 BFS
    deque<pair<pair<int, int>, pair<int, int>>> dq;
    dist[0][xs][ys] = dist[1][xs][ys] = 0;
    dq.push_front({{0, 0}, {xs, ys}});
    dq.push_back({{0, 1}, {xs, ys}});
    while (!dq.empty()) {
        int cost = dq.front().first.first;
        int dir = dq.front().first.second;
        int x = dq.front().second.first;
        int y = dq.front().second.second;
        dq.pop_front();
        for (int i = 0; i < 2; i++) {
            int nx = x + dx[dir][i];
            int ny = y + dy[dir][i];
            if (inside(nx, ny) && a[nx][ny] && cost < dist[dir][nx][ny]) {
                dist[dir][nx][ny] = cost;
                dq.push_front({{cost, dir}, {nx, ny}});
            }
        }
        for (int i = 0; i < 2; i++) {
            int nx = x + dx[1 ^ dir][i];
            int ny = y + dy[1 ^ dir][i];
            if (inside(nx, ny) && a[nx][ny]) {
                if (cost + 1 < dist[1 ^ dir][nx][ny]) {
                    dist[1 ^ dir][nx][ny] = cost + 1;
                    dq.push_back({{cost + 1, 1 ^ dir}, {nx, ny}});
                }
            }
        }
    }
    g << min(dist[0][xe][ye], dist[1][xe][ye]);
    return 0;
}

