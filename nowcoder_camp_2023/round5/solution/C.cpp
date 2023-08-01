#include <bits/stdc++.h>
#define endl '\n'
using namespace std;

void solve()
{
	int n; cin >> n;
	vector<bool> st1(n + 1), st2(n + 1);
	for (int i = 1; i <= n; i ++)
		for (int j = 1; j <= n; j ++)
		{
			int x; cin >> x;
			if (x) st1[j] = true, st2[i] = true;
		}

	int res1 = 0;
	for (int i = 1; i <= n; i ++)
		if (st1[i]) res1 ++;

	int res2 = 0;
	for (int i = 1; i <= n; i ++)
		if (st2[i]) res2 ++;

	cout << min(res1, res2) << endl;

};

signed main()
{
	ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
	int T = 1; //cin >> T;
	while (T --) solve();
	return 0;
}