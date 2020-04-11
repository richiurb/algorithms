#include <iostream>
#include <stdio.h>
#include <vector>
#include <queue>

using namespace std;

const int inf1 = 1e9;
const int inf2 = 3e4 + 1;

vector<vector<pair<int, int> > > mem(inf2);
int dist[inf2];
int n;

void dijkstra(int s) {
	for (int i = 1; i <= n; ++i) {
		dist[i] = inf1;
	}
	dist[s] = 0;

	priority_queue<pair<int, int>, vector< pair<int, int> >, greater< pair<int, int> > > dist_q;
	dist_q.push(make_pair(0, s));
	while (!dist_q.empty()) {
		pair<int, int> v = dist_q.top();
		dist_q.pop();

		if (inf1 == dist[v.second]) {
			break;
		}
		if (v.first > dist[v.second]) {
			continue;
		}

		for (pair<int, int> e : mem[v.second]) {
			int j = e.first;
			int len = e.second;
			if (dist[j] > dist[v.second] + len) {
				dist[j] = dist[v.second] + len;
				dist_q.push(make_pair(dist[j], j));
			}
		}
	}
}

int main() {
	freopen("pathbgep.in", "r", stdin);
	freopen("pathbgep.out", "w", stdout);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	int m;
	cin >> n >> m;

	for (int i = 0; i < m; ++i) {
		int a, b;
		int c;
		cin >> a >> b >> c;
		mem[a].push_back(make_pair(b, c));
		mem[b].push_back(make_pair(a, c));
		if (a == 1) {
			dist[b] = c;
		}
		if (b == 1) {
			dist[b] = c;
		}
	}

	dijkstra(1);

	for (int i = 1; i <= n; ++i) {
		cout << dist[i] << " ";
	}
}
