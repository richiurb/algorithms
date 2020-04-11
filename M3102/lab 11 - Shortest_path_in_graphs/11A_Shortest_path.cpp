#include <iostream>
#include <stdio.h>
#include <vector>

using namespace std;

const long long inf1 = 1e13;
const int inf2 = 2e3 + 1;

long long mem[inf2][inf2];
long long dist[inf2];
bool used[inf2];
int n;

void dijkstra(int s) {
	for (int i = 1; i <= n; ++i) {
		dist[i] = inf1;
		used[i] = false;
	}
	dist[s] = 0;

	for (int i = 1; i <= n; ++i) {
		int v = 0;
		for (int j = 1; j <= n; ++j) {
			if ((!used[j]) && ((v == 0) || (dist[j] < dist[v]))) {
				v = j;
			}
		}

		if (dist[v] == inf1) {
			break;
		}
		used[v] = true;

		for (int j = 1; j <= n; ++j) {
			if ((v != j) && (mem[v][j] != -1)) {
				if (dist[v] + mem[v][j] < dist[j]) {
					dist[j] = dist[v] + mem[v][j];
				}
			}
		}
	}
}

int main() {
	freopen("pathmgep.in", "r", stdin);
	freopen("pathmgep.out", "w", stdout);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int s, v;
	cin >> n >> s >> v;

	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			cin >> mem[i][j];
		}
	}

	dijkstra(s);

	if (dist[v] == inf1) {
		cout << -1;
	}
	else {
		cout << dist[v];
	}
}
