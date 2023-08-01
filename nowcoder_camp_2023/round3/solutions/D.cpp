#include <bits/stdc++.h>
using namespace std;

const int INF = 0x3f3f3f3f;

string inv(const string& s)
{
	string res;
	for (char c : s)
		res += (c == '1' ? '0' : '1');
	return res;
}

void solve()
{
	int n; cin >> n;
	vector<string> g(n, string(n, 0)), b(n, string(n, 0));
	for (int i = 0; i < n; i ++)
		cin >> g[i];

	auto work1 = [&](vector<string> g, char target)
	{
		int res = 0;
		string t = g[0], inv_t = inv(g[0]);
		for (int i = 0; i < n; i ++) if (t[i] == target) res ++;
		for (int i = 1; i < n; i ++)
		{
			if (g[i] == t) continue;
			if (g[i] == inv_t) { res ++; continue; }
			return INF;
		}
		return res;
	};

	auto work2 = [&](vector<string> g, char target)
	{
		int res = 1;
		string t = inv(g[0]), inv_t = g[0];
		for (int i = 0; i < n; i ++) if (t[i] == target) res ++;
		for (int i = 1; i < n; i ++)
		{
			if (g[i] == t) continue;
			if (g[i] == inv_t) { res ++; continue; }
			return INF;
		}
		return res;
	};

	int res = INF;
	res = min({res, work1(g, '0'), work1(g, '1')});
	res = min({res, work2(g, '0'), work2(g, '1')});

	for (int i = 0; i < n; i ++)
		for (int j = 0; j < n; j ++)
			b[j][i] = g[i][j];

	res = min({res, work1(b, '0'), work1(b, '1')});
	res = min({res, work2(b, '0'), work2(b, '1')});

	if (res == INF) cout << -1 << endl;
	else cout << res << endl;

}

signed main()
{
	ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
	int T = 1; //cin >> T;
	while (T --) solve();
	return 0;
}


