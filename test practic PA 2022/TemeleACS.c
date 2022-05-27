#include <bits/stdc++.h>
using namespace std;

const int NMAX = 1e5;
int a[NMAX + 1];
vector<int> graph[NMAX + 1];
int color[NMAX + 1];
bool vis[NMAX + 1];
vector<int> topSort;
bool isCycle = false;

void dfs(int x) {
    color[x] = 1;
    for(int i = 0; i < (int)graph[x].size(); i++) {
        int next = graph[x][i];
        if(!color[next]) {
            dfs(next);
        } else {
            if(color[next] == 1) {
                isCycle = true;
            }
        }
    }
    color[x] = 2;
}

void findTopSort(int x) {
    vis[x] = 1;
    for(int i = 0; i < (int)graph[x].size(); i++) {
        int next = graph[x][i];
        if(!vis[next]) {
            findTopSort(next);
        }
    }
    topSort.push_back(x);
}

int main() {
    int n, k;
    cin >> n >> k;
    for(int i = 1; i <= k; i++) {
        cin >> a[i];
    }
    for(int i = 1; i <= n; i++) {
        int nr;
        cin >> nr;
        for(int j = 1; j <= nr; j++) {
            int x;
            cin >> x;
            graph[i].push_back(x);
        }
    }
    for(int i = 1; i <= k; i++) {
        if(!color[a[i]]) {
            dfs(a[i]);
        }
    }
    if(isCycle) {
        cout << -1;
    } else {
        for(int i = 1; i <= k; i++) {
            if(!vis[a[i]]) {
                findTopSort(a[i]);
            }
        }
        cout << topSort.size() << '\n';
        sort(topSort.begin(), topSort.end());
        for(int i = 0; i < (int)topSort.size(); i++) {
            cout << topSort[i] << ' ';
        } 
    }
    return 0;
}