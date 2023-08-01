#include <bits/stdc++.h>
using namespace std;

void solve()
{
	int n, a, b, c; cin >> n >> a >> b >> c;
	if (n % 2)
	{
		if ((a + b + c) % 2) puts("Bob");
		else puts("Alice");
	}
	else puts("Alice");
}

signed main()
{
	ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
	int T = 1; cin >> T;
	while (T --) solve();
	return 0;
}