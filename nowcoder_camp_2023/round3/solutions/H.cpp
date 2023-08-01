#include <bits/stdc++.h>
using namespace std;
using LL = long long;

bool is_prime(LL x)
{
	if (x < 2) return false;
	for (LL i = 2; i <= x / i; i ++ )
		if (x % i == 0)
			return false;
	return true;
}

void solve()
{
	int n; cin >> n;
	LL s = 0;
	for (int i = 1; i <= n; i ++)
	{
		int x; cin >> x;
		s += x;
	}
	if (n >= 3)
	{
		s -= (n - 3) * 2;
		if (s > 5) puts("Yes");
		else puts("No");
	}
	else if (n == 2)
	{
		if (s % 2 == 0)
		{
			if (s > 2) puts("Yes");
			else puts("No");
		}
		else
		{
			if (is_prime(s - 2)) puts("Yes");
			else puts("No");
		}
	}
	else if (n == 1)
	{
		if (is_prime(s)) puts("Yes");
		else puts("No");
	}

}

signed main()
{
	ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
	int T = 1; //cin >> T;
	while (T --) solve();
	return 0;
}