#include <bits/stdc++.h>
using namespace std;
using LL = long long;

const LL MOD = 998244353;

LL qmi(LL a, LL k)
{
	LL res = 1;
	for (; k; k >>= 1, a = a * a % MOD)
		if (k & 1)
			res = res * a % MOD;
	return res;
}

LL inv(LL a) { return qmi(a, MOD - 2); }


void solve()
{
	LL n, m; cin >> n >> m;
	m += n;
	LL res = 1;
	while (n < m)
	{
		LL max_lose = log2(n + 1);
		LL next_n = min(m, (LL)pow(2, max_lose + 1) - 1);
		LL p = (1 - inv(qmi(2ll, max_lose)) + MOD) % MOD;
		res = (res * qmi(p, next_n - n)) % MOD;
		n = next_n;
	}
	cout << res << endl;
}

signed main()
{
	ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
	int T = 1; //cin >> T;
	while (T --) solve();
	return 0;
}