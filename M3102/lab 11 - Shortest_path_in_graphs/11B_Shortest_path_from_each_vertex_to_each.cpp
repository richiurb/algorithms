#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;

const int inf1 = 2e2 + 1;
const long long inf2 = 2e13;

vector<vector<pair<int, int> > > mem(inf1);
long long dist[inf1][inf1];
int n;

void floyd() {
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			for (int v = 1; v <= n; ++v) {
				dist[j][v] = min(dist[j][v], dist[j][i] + dist[i][v]);
			}
		}
	}
}

int main() {
	freopen("pathsg.in", "r", stdin);
	freopen("pathsg.out", "w", stdout);
	int m;
	cin >> n >> m;
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			dist[i][j] = inf2;
			if (i == j) {
				dist[i][j] = 0;
			}
		}
	}

	for (int i = 0; i < m; ++i) {
		int a, b, c;
		cin >> a >> b >> c;
		dist[a][b] = (long long)c;
	}

	floyd();

	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			cout << dist[i][j] << " ";
		}
		cout << "\n";
	}
}
