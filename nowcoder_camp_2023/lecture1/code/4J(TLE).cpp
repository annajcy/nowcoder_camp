#include <bits/stdc++.h>
using namespace std;

const int MOD = 998244353;

void solve()
{
	int n, m;
	cin >> n >> m;
	vector<vector<int>> f(n + 1, vector<int>(2 * (m + 1)));
	int N = m + 1;
	for (int i = -m; i <= m; i++) f[1][i + N] = 1;
	for (int i = 2; i <= n; i++)
	{
		for (int j = -m; j < 0; j++)
			for (int k = -j; k <= m; k++)
				f[i][j + k + N] = (f[i][j + k + N] + f[i - 1][j + N]) % MOD;

		for (int j = 0; j <= m; j++)
			for (int k = -j; k <= m; k++)
				f[i][k + N] = (f[i][k + N] + f[i - 1][j + N]) % MOD;
	}

	int res = 0;
	for (int i = -m; i <= m; i++) res = (res + f[n][i + N]) % MOD;
	cout << res << endl;
}

signed main()
{
	ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
	int T = 1; // cin >> T;
	while (T--) solve();
	return 0;
}