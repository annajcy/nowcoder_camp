#include <bits/stdc++.h>
#define ll long long
#define pb emplace_back
#define mp make_pair
#define orz 1000000007
#define fi first
#define se second
#pragma GCC optimize("O2")
using namespace std;
int n, f[1005], f2[1005], cnt, a[1005][1005];
pair<int, int> g[1005][1005];
pair<pair<int, int>, int> v[2000005];
void sol(int x, int y, int n, int k, int _, int id)
{
	if (!k)
	{
		v[id] = mp(mp(x, y), n);
		if (!f2[n])
			return;
		sol(x, y, f2[n], 0, 0, ++cnt);
		sol(x, y, n, f2[n], 0, id);
		return;
	}
	int m = n - k;
	if (k == m)
	{
		if (_ != 0)
			sol(x, y, k, 0, 0, ++cnt);
		if (_ != 1)
			sol(x, y + k, k, 0, 0, ++cnt);
		if (_ != 2)
			sol(x + k, y + k, k, 0, 0, ++cnt);
		if (_ != 3)
			sol(x + k, y, k, 0, 0, ++cnt);
		return;
	}
	if (k > m)
	{
		if (_ == 0)
		{
			sol(x + k, y, m, 0, 0, ++cnt);
			sol(x, y + k, m, 0, 0, ++cnt);
			sol(x + m, y + m, k, k - m, 0, id);
		}
		else if (_ == 1)
		{
			sol(x, y, m, 0, 0, ++cnt);
			sol(x + k, y + k, m, 0, 0, ++cnt);
			sol(x + m, y, k, k - m, 1, id);
		}
		else if (_ == 2)
		{
			sol(x + k, y, m, 0, 0, ++cnt);
			sol(x, y + k, m, 0, 0, ++cnt);
			sol(x, y, k, k - m, 2, id);
		}
		else
		{
			sol(x, y, m, 0, 0, ++cnt);
			sol(x + k, y + k, m, 0, 0, ++cnt);
			sol(x, y + m, k, k - m, 3, id);
		}
		return;
	}
	if (_ == 0)
	{
		sol(x + k, y, m, 0, 0, ++cnt);
		sol(x + m, y + m, k, 0, 0, ++cnt);
		sol(x, y + k, m, m - k, 3, id);
	}
	else if (_ == 1)
	{
		sol(x, y, m, 0, 0, ++cnt);
		sol(x + m, y, k, 0, 0, ++cnt);
		sol(x + k, y + k, m, m - k, 0, id);
	}
	else if (_ == 2)
	{
		sol(x, y + k, m, 0, 0, ++cnt);
		sol(x, y, k, 0, 0, ++cnt);
		sol(x + k, y, m, m - k, 1, id);
	}
	else
	{
		sol(x + k, y + k, m, 0, 0, ++cnt);
		sol(x, y + m, k, 0, 0, ++cnt);
		sol(x, y, m, m - k, 2, id);
	}
}

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i)
	{
		f[i] = i * i;
		for (int j = 1; j < i; ++j)
		{
			if (j * 2 >= i)
				g[i][j] = g[j][j * 2 - i], g[i][j].fi = max(g[i][j].fi, f[i - j]), g[i][j].se += 2;
			else
				g[i][j] = g[i - j][i - j * 2], g[i][j].fi = max(g[i][j].fi, max(f[j], f[i - j])), g[i][j].se += 2;
			int o = max(max(g[i][j].fi, f[j]), 1 + g[i][j].se);
			if (o < f[i])
				f[i] = o, f2[i] = j;
		}
		g[i][0] = mp(f[i], 1);
	}
	sol(1, 1, n, 0, 0, cnt = 1);
	for (int i = 1; i <= n; ++i)
	{
		for (int j = 1; j <= n; ++j)
			a[i][j] = 1;
	}
	int res = 0;
	for (int i = cnt; i; --i)
		if (a[v[i].fi.fi][v[i].fi.se] != v[i].se)
			++res, a[v[i].fi.fi][v[i].fi.se] = v[i].se;
	printf("%d\n", res);
	for (int i = 1; i <= n; ++i)
	{
		for (int j = 1; j <= n; ++j)
			a[i][j] = 1;
	}
	for (int i = cnt; i; --i)
	{
		if (a[v[i].fi.fi][v[i].fi.se] != v[i].se)
			printf("%d %d %d\n", v[i].fi.fi, v[i].fi.se, v[i].se), a[v[i].fi.fi][v[i].fi.se] = v[i].se;
	}
	return 0;
}
