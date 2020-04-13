#include <iostream>
#include <stdio.h>
#include <vector>

using namespace std;

const long long inf1 = 8e18;
const int inf2 = 2e3 + 1;

struct edge {
	int from, to;
	long long weight;

	edge() {}

	edge(int from, int to, long long weight) {
		(*this).from = from;
		(*this).to = to;
		(*this).weight = weight;
	}
};

vector<edge> mem;
vector<vector<int> > mem_dfs(inf2);
long long dist[inf2];
bool neg[inf2];
bool used[inf2];

void dfs(int s) {
	used[s] = true;
	for (int e : mem_dfs[s]) {
		if (!used[e]) {
			dfs(e);
		}
	}
}

int main() {
	freopen("path.in", "r", stdin);
	freopen("path.out", "w", stdout);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int n, m, s;
	cin >> n >> m >> s;
	for (int i = 0; i < m; ++i) {
		edge e;
		cin >> e.from >> e.to >> e.weight;
		mem.push_back(e);
		mem_dfs[e.from].push_back(e.to);
	}

	for (int i = 1; i <= n; ++i) {
		dist[i] = inf1;
		neg[i] = false;
		used[i] = false;
	}

	dist[s] = 0;
	bool any = true;
	for (int i = 1; i <= n; ++i) {
		for (edge e : mem) {
			if (dist[e.from] < inf1) {
				if (dist[e.to] > dist[e.from] + e.weight) {
					dist[e.to] = dist[e.from] + e.weight;
					if (dist[e.to] < -inf1) {
						dist[e.to] = -inf1;
					}
				}
			}
		}
	}

	for (edge e : mem) {
		if (dist[e.from] < inf1) {
			if (dist[e.to] > dist[e.from] + e.weight) {
				dist[e.to] = dist[e.from] + e.weight;
				if (dist[e.to] < -inf1) {
					dist[e.to] = -inf1;
				}
				neg[e.to] = true;
			}
		}
	}

	for (int i = 1; i <= n; ++i) {
		if (neg[i]) {
			dfs(i);
		}
		for (int j = 1; j <= n; ++j) {
			if (used[j] && !neg[j]) {
				neg[j] = true;
			}
			used[j] = false;
		}
	}

	for (int i = 1; i <= n; ++i) {
		if (neg[i]) {
			cout << "-" << "\n";
		}
		else if ((dist[i] < inf1)) {
			cout << dist[i] << "\n";
		}
		else {
			cout << "*" << "\n";
		}
	}
}
