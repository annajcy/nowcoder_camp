#include <bits/stdc++.h>
using namespace std;

void solve()
{
	int n, m, k; cin >> n >> m >> k;
	vector<vector<int>> g(n, vector<int>(m));
	for (int i = 0; i < n; i ++)
		for (int j = 0; j < m; j ++)
			cin >> g[i][j];

	vector<bool> st(m + 1, false);
	vector<int> res;
	for (int i = k - 1; i >= 0; i --)
	{
		int cur = i % n;
		int t = -1;
		for (int j = 0; j < m; j ++)
		{
			if (st[j]) continue;
			if (t == -1 || g[cur][j] > g[cur][t]) t = j;
		}
		st[t] = true;
		res.push_back(t + 1);
	}
	sort(res.begin(), res.end());
	for (auto i : res) cout << i << ' '; cout << endl;
}

signed main()
{
	ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
	int T = 1; cin >> T;
	while (T --) solve();
	return 0;
}