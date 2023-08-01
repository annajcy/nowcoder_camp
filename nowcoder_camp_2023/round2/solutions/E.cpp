#include <bits/stdc++.h>
using namespace std;

using LL = long long;

const int INF = 1e9;

LL sqrt(LL x)
{
	LL l = 1, r = INF;
	while (l < r)
	{
		LL mid = (l + r + 1) >> 1;
		if (mid * mid <= x) l = mid;
		else r = mid - 1;
	}
	return r;
}

void solve()
{
	LL x; cin >> x;
	for (int i = 0; i < 18; i ++)
	{
		LL t = pow(10, i), a = sqrt(x * t);
		if (a > INF) { cout << -1 << endl; return; }
		if (a * a / t == x) { cout << a << endl; return; }
		if ((a + 1) * (a + 1) / t == x) { cout << a + 1 << endl; return; }
	}
	cout << -1 << endl;
}

signed main()
{
	ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
	int T = 1; cin >> T;
	while (T --) solve();
	return 0;
}