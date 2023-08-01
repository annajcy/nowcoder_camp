#include <bits/stdc++.h>
using namespace std;

void solve()
{
	int n, m; cin >> n >> m;
	vector<vector<int>> g(n + 1);
	vector<int> din(n + 1), res;
	while (m --)
	{
		int u, v; cin >> u >> v;
		g[u].push_back(v);
		din[v] ++;
	}

	auto topo = [&]() -> bool {
		queue<int> q;
		for (int i = 1; i <= n; i ++)
			if (!din[i]) q.push(i);

		while (!q.empty())
		{
			int u = q.front(); q.pop(); res.push_back(u);
			for (auto v : g[u])
				if (-- din[v] == 0)
					q.push(v);
		}
		return res.size() == n;
	};

	if (topo())
	{
		cout << 1 << endl;
		for (auto i: res) cout << i << ' '; cout << endl;
	}
	else
	{
		cout << 2 << endl;
		for (int i = 1; i <= n; i ++) cout << i << ' '; cout << endl;
		for (int i = n; i >= 1; i --) cout << i << ' '; cout << endl;
	}
}

signed main()
{
	ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
	int T = 1; //cin >> T;
	while (T --) solve();
	return 0;
}


