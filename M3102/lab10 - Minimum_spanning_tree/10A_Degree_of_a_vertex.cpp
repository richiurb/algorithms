#include <iostream>
#include <vector>
#include <stdio.h>

using namespace std;

const int e = 1e2 + 1;

vector<vector<int> > vec(e);

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	int n, m;
	cin >> n >> m;

	for (int i = 0; i < m; i++) {
		int a, b;
		cin >> a >> b;
		vec[a].push_back(b);
		vec[b].push_back(a);
	}

	for (int i = 1; i <= n; i++) {
		cout << vec[i].size() << " ";
	}
}
