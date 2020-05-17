#include <iostream>
#include <vector>
#include <stdio.h>
#include <algorithm>

using namespace std;

const int e = 1e2 + 1;
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

int n;
int used[e];
vector<vector<edge>> graph(e);

int DFSFord(int v, int f_now) {
    if (v == n) return f_now;
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
    freopen("maxflow.in", "r", stdin);
    freopen("maxflow.out", "w", stdout);
    int m;
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        used[i] = false;
    }

    for (int i = 0; i < m; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        edge first(b, c, 0);
        edge second(a, 0, 0);
        graph[a].push_back(first);
        graph[b].push_back(second);

    }

    int t = DFSFord(1, INF);
    while (t != 0) {
        for (int i = 1; i <= n; ++i)
            used[i] = false;
        t = DFSFord(1, INF);
    }

    int result = 0;
    for (edge v : graph[1]) 
        result += v.current_flow;
    cout << result;
}
