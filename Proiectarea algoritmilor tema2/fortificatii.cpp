#include <bits/stdc++.h>
using namespace std;

typedef pair<long long, int> PII;

ifstream f("fortificatii.in");
ofstream g("fortificatii.out");

const long long INF = 1e15;
const int NMAX = 1e5;
bool b[NMAX + 1];
bool vis[NMAX + 1];
long long dist[NMAX + 1];
vector<pair<int, long long>> graph[NMAX + 1];
vector<long long> d;
int n, m, nb;
long long k;

bool check(long long value) {
    long long sum = 0;
    for (int i = 0; i < (int)d.size(); i++) {
        if (d[i] < value) {
            sum += value - d[i];
        }
    }
    return sum <= k;
}


int main() {
    f >> n >> m >> k;
    f >> nb;
    for (int i = 1; i <= nb; i++) {
        int x;
        f >> x;
        b[x] = true;
    }
    while (m--) {
        int x, y;
        long long c;
        f >> x >> y >> c;
        graph[x].push_back({y, c});
        graph[y].push_back({x, c});
    }
    // Dijkstra
    for (int i = 1; i <= n; i++) {
        dist[i] = INF;
    }
    dist[1] = 0;
    priority_queue<PII, vector<PII>, greater<PII>> pq;
    pq.push({0, 1});
    while (!pq.empty()) {
        PII node = pq.top();
        pq.pop();
        if (vis[node.second]) {
            continue;
        }
        vis[node.second] = true;
        for (int i = 0; i < (int)graph[node.second].size(); i++) {
            int next = graph[node.second][i].first;
            long long cost = graph[node.second][i].second;
            if (b[next]) {
                continue;
            }
            if (node.first + cost < dist[next]) {
                dist[next] = node.first + cost;
                pq.push({dist[next], next});
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        if (!b[i] && dist[i] != INF) {
            for (int j = 0; j < (int)graph[i].size(); j++) {
                int next = graph[i][j].first;
                long long cost = graph[i][j].second;
                if (b[next]) {
                    d.push_back(dist[i] + cost);
                }
            }
        }
    }
    // cautam binar raspunsul
    sort(d.begin(), d.end());
    long long st = d[0];
    long long dr = d[0] + k;
    long long sol = st;
    while (st <= dr) {
        long long mid = (st + dr) / 2;
        if (check(mid)) {
            sol = mid;
            st = mid + 1;
        } else {
            dr = mid - 1;
        }
    }
    g << sol;
    return 0;
}
