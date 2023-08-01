#include <bits/stdc++.h>
#define endl '\n'
using namespace std;
using LL = long long;

const int MOD = 998244353;

void solve()
{
	int n, m; cin >> n >> m;
	vector<vector<LL>> f(n + 1, vector<LL>(2 * (m + 1)));
	int N = m + 1;
	for (int i = -m; i <= m; i ++) f[1][i + N] = 1;
	for (int i = 2; i <= n; i ++)
	{
		vector<LL> sum(2 * (m + 1));
		for (int j = -m; j <= m; j ++) sum[j + N] = (sum[j - 1 + N] + f[i - 1][j + N]) % MOD;
		auto get = [&](int l, int r)
				{ return (sum[r + N] - sum[l - 1 + N] + MOD) % MOD; };

		for (int jk = 0, l = -m; jk < m; jk ++, l ++)
			f[i][jk + N] = ((f[i][jk + N] + get(l, -1))) % MOD;

		for (int k = -m, l = m; k < 0; k ++, l --)
			f[i][k + N] = (f[i][k + N] + get(l, m));

		for (int k = 0; k <= m; k ++)
			f[i][k + N] = (f[i][k + N] + get(0, m));
	}

	LL res = 0;
	for (int i = -m; i <= m; i ++) res = (res + f[n][i + N]) % MOD;
	cout << res << endl;
}

signed main()
{
	ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
	int T = 1; //cin >> T;
	while (T --) solve();
	return 0;
}