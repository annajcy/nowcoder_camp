#include <bits/stdc++.h>
#define endl '\n'
using namespace std;

void solve()
{
	int n, m; cin >> n >> m;
	vector<vector<int>> g(n + 1);
	while (m --)
	{
		int u, v; cin >> u >> v;
		g[u].push_back(v);
	}

	vector<int> dist(n + 1, -1);
	auto bfs = [&](int s)
	{
		queue<int> q;
		q.push(s); dist[s] = 0;
		while (!q.empty())
		{
			int u = q.front(); q.pop();
			for (auto &v : g[u])
			{
				if (~dist[v]) continue;
				dist[v] = dist[u] + 1;
				q.push(v);
			}
		}
	};

	vector<bool> vis(n + 1);
	bool res = true;
	function<void(int)> dfs = [&](int u)
	{
		vis[u] = true;
		for (auto &v : g[u])
		{
			if (vis[v]) continue;
			if (dist[v] != dist[u] + 1)
			{
				res = false;
				return;
			}
			dfs(v);
		}
		vis[u] = false;
	};

	bfs(1);
	dfs(1);

	if (res) puts("Yes");
	else puts("No");
}

signed main()
{
	ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
	int T = 1; cin >> T;
	while (T --) solve();
	return 0;
}