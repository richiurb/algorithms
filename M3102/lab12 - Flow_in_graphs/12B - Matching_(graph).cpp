#include <iostream>
#include <vector>
#include <stdio.h>
#include <algorithm>

using namespace std;

const int e = 4e2 + 2;
const int INF = 1e9;

struct edge {
    int to;
    int cap;
    int current_flow;

    edge(int to, int capacity, int current_flow) {
        (*this).to = to;
        (*this).cap = capacity;
        (*this).current_flow = current_flow;
    }

    edge() {
        to = 1;
        cap = 0;
        current_flow = 0;
    }
};

int n, m;
int used[e];
vector<vector<edge>> graph(e);

int DFSFord(int v, int f_now) {
    if (v == n + m + 1) return f_now;
    used[v] = true;

    for (int i = 0; i < graph[v].size(); ++i) {
        if ((!used[graph[v][i].to]) && (graph[v][i].cap != graph[v][i].current_flow)) {
            int delta = DFSFord(graph[v][i].to, min(f_now, graph[v][i].cap - graph[v][i].current_flow));
            if (delta > 0) {
                graph[v][i].current_flow += delta;
                for (int j = 0; j < graph[graph[v][i].to].size(); ++j) {
                    if (graph[graph[v][i].to][j].to == v) {
                        graph[graph[v][i].to][j].current_flow -= delta;
                    }
                }
                return delta;
            }
        }
    }        
    return 0;
}

int main() {
    //freopen("maxflow.in", "r", stdin);
    //freopen("maxflow.out", "w", stdout);
    int k;
    cin >> n >> m >> k;
    for (int i = 0; i <= n + m + 1; ++i) {
        used[i] = false;
    }

    for (int i = 1; i <= n; ++i) {
        edge zero(i, 1, 0);
        edge zero_s(0, 0, 0);
        graph[0].push_back(zero);
        graph[i].push_back(zero_s);
    }

    for (int i = 0; i < k; ++i) {
        int a, b;
        cin >> a >> b;
        edge first(b + n, 1, 0);
        edge second(a, 0, 0);
        graph[a].push_back(first);
        graph[b + n].push_back(second);
    }

    for (int i = n + 1; i <= n + m; ++i) {
        edge zero(n + m + 1, 1, 0);
        edge zero_s(i, 0, 0);
        graph[i].push_back(zero);
        graph[n + m + 1].push_back(zero_s);
    }

    int t = DFSFord(0, INF);
    while (t != 0) {
        for (int i = 0; i <= n + m + 1; ++i)
            used[i] = false;
        t = DFSFord(0, INF);
    }

    int result = 0;
    for (edge v : graph[0]) 
        result += v.current_flow;
    cout << result;
}
