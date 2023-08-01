#include <bits/stdc++.h>
using namespace std;

using LL = long long;
const int INF = 0x3f3f3f3f;

void solve()
{
	int n; cin >> n;
	vector<int> st(n + 1), a(n + 1), p(1);
	for (int i = 1; i <= n; i ++) cin >> a[i];
	for (int i = 1; i <= n; i ++)
	{
		cin >> st[i];
		if (st[i]) p.push_back(i);
	}
	int ln = p.size() - 1;
	if (!ln) { cout << 0 << endl; return; }
	vector<vector<LL>> f(ln + 1, vector<LL>(3, -INF));
	f[1][1] = a[p[1]];
	if (p[1] - 1 >= 1) f[1][0] = a[p[1] - 1];
	if (p[1] + 1 <= n) f[1][2] = a[p[1] + 1];
	for (int i = 2; i <= ln; i ++)
		for (int j = 0; j <= 2; j ++)
			for (int k = 0; k <= 2; k ++)
				if (p[i - 1] + k - 1 < p[i] + j - 1 && p[i] + j - 1 <= n)
					f[i][j] = max(f[i][j], f[i - 1][k] + a[p[i] + j - 1]);


	cout << max({f[ln][0], f[ln][1], f[ln][2]}) << endl;
}

signed main()
{
	ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
	int T = 1; //cin >> T;
	while (T --) solve();
	return 0;
}