#include <iostream>
#include <vector>
#include <stdio.h>
#include <cmath>
#include <iomanip>
#include <algorithm>
#include <queue>

using namespace std;

const int e = 8e3 + 1;
const int INF = 1000000000;

int x[e];
int y[e];
double dist[e];
bool used[e];

int main() {
	//freopen("spantree.in", "r", stdin);
	//freopen("spantree.out", "w", stdout);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout << setprecision(20);
	int m;
	cin >> m;

	for (int i = 1; i <= m; i++) {
		cin >> x[i] >> y[i];
		dist[i] = INF;
		used[i] = 0;
	}

	dist[1] = 0;

	for (int j = 1; j <= m; j++) {
		double min = INF;
		int min_c = 0;
		for (int i = 1; i <= m; i++) {
			if ((min > dist[i]) && (!used[i])) {
				min = dist[i];
				min_c = i;
			}
		}

		used[min_c] = 1;

		for (int i = 1; i <= m; i++) {
			if ((i != min_c) && (!used[i])) {
				double dist_f = sqrt((x[i] - x[min_c]) * (x[i] - x[min_c]) + (y[i] - y[min_c]) * (y[i] - y[min_c]));
				if (dist_f < dist[i]) {
					dist[i] = dist_f;
				}
			}
		}
	}

	long double sum = 0;

	for (int i = 1; i <= m; i++) {
		sum += (long double)dist[i];
	}

	cout << sum;
}