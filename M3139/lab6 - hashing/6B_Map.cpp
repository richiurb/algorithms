#include <iostream>
#include <stdio.h>
#include <vector>
#include <stdlib.h>
#include <algorithm>

using namespace std;

const int e = 1e6;

vector<vector<pair<string, string> > > vec(e);

int main() {
	freopen("map.in", "r", stdin);
	freopen("map.out", "w", stdout);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	string operation;
	while (cin >> operation) {
		string num;
		cin >> num;
		int hash_func_l = 0;
		for (int i = 0; i < min((int)num.size(), 10); i++) {
			hash_func_l = (hash_func_l +
				(abs(num[(int)num.size() - i - 1] * 31 * 31 + (int)num[i] * 101))) % e;
		}
		int hash_func = (int)(hash_func_l % e);

		if (operation == "put") {
			string s;
			cin >> s;
			bool flag = true;
			if (!vec[hash_func].empty()) {
				for (int i = 0; i < (int)vec[hash_func].size(); i++) {
					if (vec[hash_func][i].first == num) {
						vec[hash_func][i].second = s;
						flag = false;
						break;
					}
				}
			}
			if (flag) {
				vec[hash_func].push_back(make_pair(num, s));
			}
		}

		if (operation == "delete") {
			bool flag = false;
			int a = 0;
			if (!vec[hash_func].empty()) {
				for (int i = 0; i < (int)vec[hash_func].size(); i++) {
					if (vec[hash_func][i].first == num) {
						a = i;
						flag = true;
						break;
					}
				}
				if (flag) {
					vec[hash_func][a] = vec[hash_func][(int)vec[hash_func].size() - 1];
					vec[hash_func].pop_back();
				}
			}
		}

		if (operation == "get") {
			if (vec[hash_func].empty()) {
				cout << "none\n";
			} else {
				bool flag = false;
				for (int i = 0; i < (int)vec[hash_func].size(); i++) {
					if (vec[hash_func][i].first == num) {
						cout << vec[hash_func][i].second << "\n";
						flag = true;
						break;
					}
				}
				if (!flag) {
					cout << "none\n";
				}
			}
		}
	}
}
