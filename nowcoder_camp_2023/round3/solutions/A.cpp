#include <bits/stdc++.h>
using namespace std;
using LL = long long;

LL to_ll(string s)
{
	LL res = 0;
	for (int i = 0; i <= s.size() - 1; i ++)
		res = res * 2 + (s[i] - '0');
	return res;
}

void solve()
{
	string x, y; cin >> x >> y;
	LL a = to_ll(x), b = to_ll(y);
	if (a == 0 && b == 0) { puts("0"); return; }
	if (a == 0 && b != 0) { puts("-1"); return; }
	cout << abs(a - b) << endl;
}

signed main()
{
	ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
	int T = 1; //cin >> T;
	while (T --) solve();
	return 0;
}