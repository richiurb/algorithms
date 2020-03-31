#include <iostream>
#include <stdio.h>
#include <vector>
#include <stdlib.h>

using namespace std;

const int e = 1e6;

vector<vector<int> > vec(e);

int main() {
	freopen("set.in", "r", stdin);
	freopen("set.out", "w", stdout);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	string operation;
	while (cin >> operation) {
		int num;
		cin >> num;
		int hash_func = (abs(num * 31 * 31 + num * 101 + 37)) % e;

		if (operation == "insert") {
			bool flag = true;
			if (!vec[hash_func].empty()) {
				for (int i = 0; i < (int)vec[hash_func].size(); i++) {
					if (vec[hash_func][i] == num) {
						flag = false;
						break;
					}
				}
			}
			if (flag) {
				vec[hash_func].push_back(num);
			}
		}

		if (operation == "delete") {
			bool flag = false;
			if (!vec[hash_func].empty()) {
				for (int i = 0; i < (int)vec[hash_func].size(); i++) {
					if (flag) {
						vec[hash_func][i - 1] = vec[hash_func][i];
					}
					if (vec[hash_func][i] == num) {
						flag = true;
					}
				}
				if (flag) {
					vec[hash_func].pop_back();
				}
			}
		}

		if (operation == "exists") {
			if (vec[hash_func].empty()) {
				cout << "false\n";
			} else {
				bool flag = false;
				for (int i = 0; i < (int)vec[hash_func].size(); i++) {
					if (vec[hash_func][i] == num) {
						flag = true;
						break;
					}
				}
				if (flag) {
					cout << "true\n";
				} else {
					cout << "false\n";
				}
			}
		}
	}
}
