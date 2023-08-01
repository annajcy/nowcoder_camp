#include <bits/stdc++.h>
#define endl '\n'
using namespace std;
using PII = pair<int, int>;

template <typename T>
T gcd(T a, T b)
{
	return b ? gcd(b, a % b) : a;
}

void solve()
{
	int k, c, n; cin >> k >> c >> n;

	auto get_divs = [&](int x)
	{
		vector<int> res;
		for (int i = 1; i <= x / i; i ++)
			if (x % i == 0)
			{
				if (i == x / i) res.push_back(i);
				else res.push_back(i), res.push_back(x / i);
			}
		return res;
	};

	auto get_pairs = [&](const vector<int>& bs, int k, int n)
	{
		int res = 0;
		for (auto b : bs)
		{
			if ((c - b) % k) continue;
			int a = (c - b) / k;
			if (a == 0) continue;
			if (gcd(a, b) < n) continue;
			res ++;
		}
		return res;
	};

	vector<int> b = get_divs(c);
	cout << get_pairs(b, k, n) << endl;
}

signed main()
{
	ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
	int T = 1; cin >> T;
	while (T --) solve();
	return 0;
}