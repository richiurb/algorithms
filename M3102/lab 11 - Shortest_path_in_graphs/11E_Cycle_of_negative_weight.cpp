#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>
 
using namespace std;
 
const int inf1 = 1e9;
const int inf2 = 251;
 
struct edge {
    int from;
    int to;
    int weight;
 
    edge() {}
 
    edge(int from, int to, int weight) {
        (*this).from = from;
        (*this).to = to;
        (*this).weight = weight;
    }
};
 
int n;
vector<edge> memory;
int dist[inf2];
int past[inf2];
 
int search_cycle() {
    dist[1] = 0;
    int vertex;
    for (int i = 1; i <= n; ++i) {
        vertex = -1;
        for (edge e1 : memory) {
            if (dist[e1.to] > dist[e1.from] + e1.weight) {
                dist[e1.to] = max(dist[e1.from] + e1.weight, -inf1);
                past[e1.to] = e1.from;
                vertex = e1.to;
            }
        }
    }
 
    return vertex;
}
 
int main() {
    freopen("negcycle.in", "r", stdin);
    freopen("negcycle.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n;
 
    for (int i = 1; i <= n; ++i) {
        dist[i] = inf1;
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            int w;
            cin >> w;
 
            if ((w != inf1)) {
                edge e;
                e.weight = w;
                e.from = i;
                e.to = j;
                memory.push_back(e);
            }
        }
    }
 
    int v = search_cycle();
    if (v == -1) {
        cout << "NO";
    }
    else {
        cout << "YES\n";
 
        for (int i = 1; i <= n; ++i)
            v = past[v];
 
        vector<int> path;
        int cur = v;
        while (!((cur == v) && (path.size() > 1))) {
            path.push_back(cur);
            cur = past[cur];
        }
        path.push_back(cur);
        reverse(path.begin(), path.end());
 
        cout << path.size() << "\n";
        for (int i = 0; i < path.size(); ++i)
            cout << path[i] << ' ';
    }
}
