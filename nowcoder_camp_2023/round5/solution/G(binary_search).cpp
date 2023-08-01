#include <bits/stdc++.h>
#define endl '\n'
using namespace std;

void solve()
{
	int n, k; cin >> n >> k;
	vector<int> q(n + 1);
	vector<vector<int>> s(5, vector<int> (n + 1));
	for (int i = 1; i <= n; i ++) cin >> q[i];

	for (int i = 1; i <= n; i ++)
		for (int j = 1; j <= 4; j ++)
			s[j][i] = s[j][i - 1] + (q[i] == j);

	auto is_valid = [&](int l, int r)
	{
		vector<int> v(5);
		for (int i = 1; i <= 4; i ++) v[i] = s[i][r] - s[i][l - 1];
		for (int i = 1; i <= 3; i ++)
			if (v[i] < 1) return false;
		if (v[4] < k) return false;
		return true;
	};

	auto check = [&](int len)
	{
		for (int l = 1, r = l + len - 1; r <= n; l ++, r ++)
			if (is_valid(l, r)) return true;
		return false;
	};

	int l = 3 + k, r = n;
	while (l < r)
	{
		int mid = (l + r) >> 1;
		if (check(mid)) r = mid;
		else l = mid + 1;
	}

	cout << l << endl;

}

signed main()
{
	ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
	int T = 1; //cin >> T;
	while (T --) solve();
	return 0;
}