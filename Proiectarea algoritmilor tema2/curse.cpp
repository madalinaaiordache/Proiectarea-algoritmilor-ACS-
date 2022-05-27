#include <bits/stdc++.h>
using namespace std;

ifstream f("curse.in");
ofstream g("curse.out");

const int NMAX = 20;
const int KMAX = 1e5;
const int MMAX = 1e4;
int a[KMAX + 1][NMAX + 1];
vector<int> graph[MMAX + 1];
int grad[MMAX + 1];

int main() {
    int n, m, k;
    f >> n >> m >> k;
    for (int i = 1; i <= k; i++) {
        for (int j = 1; j <= n; j++) {
            f >> a[i][j];
        }
    }
    // construim graful masinilor
    for (int i = 1; i < k; i++) {
        int j = 1;
        while (j <= n && a[i][j] == a[i + 1][j]) {
            j++;
        }
        if (j <= n) {
            graph[a[i][j]].push_back(a[i + 1][j]);
            grad[a[i + 1][j]]++;
        }
    }
    queue<int> q;
    for (int i = 1; i <= m; i++) {
        if (grad[i] == 0) {
            q.push(i);
        }
    }
    // sortare topologica
    while (!q.empty()) {
        int node = q.front();
        q.pop();
        g << node << ' ';
        for (int i = 0; i < (int)graph[node].size(); i++) {
            int next = graph[node][i];
            grad[next]--;
            if (grad[next] == 0) {
                q.push(next);
            }
        }
    }
    return 0;
}
