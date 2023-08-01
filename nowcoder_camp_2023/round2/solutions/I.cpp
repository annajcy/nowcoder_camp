#include <bits/stdc++.h>
#define int long long
using namespace std;

string c = "xo";
int n, m;

void fill(vector<vector<bool>> &res)
{

	for (int i = 0; i < n / 2; i ++)
	{
		bool st = 1;
		int x = i * 2;
		for (int j = 0; j < m; j ++)
		{
			if (j % 4 == 0) st = !st;
			res[x][j] = st, res[x + 1][j] = !st;
		}
	}
}

void solve()
{
	cin >> n >> m;
	vector<vector<bool>> res(n, vector<bool>(m));
	fill(res);
	if (n % 2)
	{
		for (int i = 0; i < m; i ++)
			if (i % 2) res[n - 1][i] = 1;
			else res[n - 1][i] = 0;
	}
	for (int i = 0; i < n; i ++)
	{
		for (int j = 0; j < m; j ++)
			cout << c[res[i][j]];
		cout << endl;
	}

}

signed main()
{
	ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
	int T = 1; cin >> T;
	while (T --) solve();
	return 0;
}