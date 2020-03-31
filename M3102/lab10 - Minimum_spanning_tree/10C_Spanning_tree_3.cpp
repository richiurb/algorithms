#include <iostream>
#include <vector>
#include <stdio.h>
#include <cmath>

using namespace std;

const int e_2 = 5e4 + 1;

vector<int> dist;
vector<int> start_v;
vector<int> end_v;

struct setItem {
	int parent;

	setItem(int a) {
		parent = a;
	}

	setItem() = default;
};

setItem s[e_2];

void merge(int left, int mid, int right) {
	int it1 = 0;
	int it2 = 0;
	int result[right - left];
	int start_r[right - left];
	int end_r[right - left];

	while ((left + it1 < mid) && (mid + it2 < right)) {
		if (dist[left + it1] <= dist[mid + it2]) {
			result[it1 + it2] = dist[left + it1];
			start_r[it1 + it2] = start_v[left + it1];
			end_r[it1 + it2] = end_v[left + it1];
			++it1;
		}
		else {
			result[it1 + it2] = dist[mid + it2];
			start_r[it1 + it2] = start_v[mid + it2];
			end_r[it1 + it2] = end_v[mid + it2];
			++it2;
		}
	}

	while (left + it1 < mid) {
		result[it1 + it2] = dist[left + it1];
		start_r[it1 + it2] = start_v[left + it1];
		end_r[it1 + it2] = end_v[left + it1];
		++it1;
	}

	while (mid + it2 < right) {
		result[it1 + it2] = dist[mid + it2];
		start_r[it1 + it2] = start_v[mid + it2];
		end_r[it1 + it2] = end_v[mid + it2];
		++it2;
	}

	for (int i = 0; i < it1 + it2; ++i) {
		dist[left + i] = result[i];
		start_v[left + i] = start_r[i];
		end_v[left + i] = end_r[i];
	}
}

void merge_sort(int n) {
	for (int i = 1; i <= n; i *= 2) {
		for (int j = 0; j <= n - i; j += 2 * i) {
			merge(j, j + i, min(j + 2 * i, n));
		}
	}
}

int find_set(int g) {
	if (s[g].parent == g) {
		return g;
	}

	return s[g].parent = find_set(s[g].parent);
}

void union_set(int a, int b) {
	int p = find_set(a);
	int q = find_set(b);

	if (p != q) {
		s[q].parent = p;
		q = find_set(b);
	}
}

int main() {
	//freopen("spantree3.in", "r", stdin);
	//freopen("spantree3.out", "w", stdout);
	int n, m;
	cin >> n >> m;

	for (int i = 0; i < m; i++) {
		int b, v, w;
		cin >> b >> v >> w;
		start_v.push_back(b);
		end_v.push_back(v);
		dist.push_back(w);
	}

	for (int i = 1; i <= n; i++) {
		s[i] = setItem(i);
	}

	int size_d = dist.size();
	if (size_d > 1) {
		merge_sort(size_d);
	}

	long long sum = 0;

	for (int i = 0; i < size_d; i++) {
		if (find_set(start_v[i]) != find_set(end_v[i])) {
			union_set(start_v[i], end_v[i]);
			sum += (long long) dist[i];
		}
	}

	cout << sum;
}
