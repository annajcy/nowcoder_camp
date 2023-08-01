#include <bits/stdc++.h>
using namespace std;
using LL = long long;


void solve()
{
	int n, m, k; cin >> n >> m >> k;
	vector<vector<int>> g(n + 1);
	for (int i = 1; i <= m; i ++)
	{
		int u, v; cin >> u >> v;
		g[u].push_back(v), g[v].push_back(u);
	}

	vector<int> dist(n + 1, -1), fa(n + 1);
	vector<bool> st(n + 1, false);

	auto bfs = [&](){
		queue<int> q;
		q.push(1), dist[1] = 0;
		while (!q.empty())
		{
			int u = q.front(); q.pop();
			for (auto v : g[u])
			{
				if (dist[v] != -1) continue;
				dist[v] = dist[u] + 1, fa[v] = u, st[u] = true;
				q.push(v);
			}
		}
	};

	bfs();

	LL res = 1;
	for (int u = 2; u <= n; u ++)
	{
		if (dist[u] == -1 || dist[u] > k) continue;
		LL cnt = 0;
		for (auto v : g[u])
		{
			if (v == fa[u] || fa[v] == u) continue;
			cnt ++;
		}
		if (!st[u]) cnt = max(cnt, 1ll);
		res += (k - dist[u]) * cnt + 1;
	}
	cout << res << endl;
}

signed main()
{
	ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
	int T = 1; //cin >> T;
	while (T --) solve();
	return 0;
}