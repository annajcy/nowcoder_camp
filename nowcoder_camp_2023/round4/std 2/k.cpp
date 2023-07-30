#include <bits/stdc++.h>
#define ll long long
#define pb emplace_back
#define mp make_pair
#define orz 1000000007
#define fi first
#define se second
#define MAXN 1505
#pragma GCC optmize("O2")
using namespace std;
int n, m, nb[MAXN][MAXN], nr[MAXN][MAXN], N, M, in[MAXN * MAXN * 2], c1[MAXN * MAXN * 2], c2[MAXN * MAXN * 2], n1[MAXN * MAXN * 2], n2[MAXN * MAXN * 2], a[MAXN], b[MAXN];
int v1[MAXN * MAXN * 2], v2[MAXN * MAXN * 2], l0[MAXN][MAXN], l1[MAXN][MAXN];
int sa[MAXN], sd[MAXN], sr[MAXN], sb[MAXN];
vector<int> v[MAXN][MAXN];
ll ans;
char c[MAXN][MAXN];
int sol(int U, int D, int L, int R)
{
	if (U + 1 >= D)
		return 0; // red
	if (L + 1 >= R)
		return 2; // blue
	int ul, ur, dl;
	if (c[U][L] == 'R')
		ul = (U - 1) * m + L;
	else
		ul = N + (U - 1) * (m - 1) + L;
	if (c[U][R] == 'R')
		ur = (U - 1) * m + R;
	else
		ur = N + (U - 1) * (m - 1) + R - 1;
	if (c[D][L] == 'R')
		dl = (D - 2) * m + L;
	else
		dl = N + (D - 1) * (m - 1) + L;
	int cnt = 0;
	if (c1[ur] != c1[dl])
	{
		if (c1[ur] == c1[ul])
			++cnt;
	}
	else
	{
		int UR = n1[ur] - n1[ul], DL = n1[dl] - n1[ul];
		if (UR < 0)
			UR += orz;
		if (DL < 0)
			DL += orz;
		if (UR < DL)
			++cnt;
	}
	if (c2[ur] != c2[dl])
	{
		if (c2[ur] == c2[ul])
			++cnt;
	}
	else
	{
		int UR = n2[ur] - n2[ul], DL = n2[dl] - n2[ul];
		if (UR < 0)
			UR += orz;
		if (DL < 0)
			DL += orz;
		if (UR < DL)
			++cnt;
	}
	return cnt; // 2 blue 1 tie 0 red
}
int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++i)
		scanf("%s", c[i] + 1);
	if (n <= 2 || m <= 2)
	{
		printf("0\n");
		return 0;
	}
	N = (n - 1) * m, M = N + (m - 1) * n;
	for (int i = n; i; --i)
	{
		for (int j = m; j; --j)
		{
			if (c[i][j] == 'B')
				nb[i][j] = max(i, nb[i + 1][j]);
			else
				nr[i][j] = max(j, nr[i][j + 1]);
		}
	}
	for (int i = 1; i < n; ++i)
	{
		for (int j = 1; j < m; ++j)
		{
			int u = N + (i - 1) * (m - 1) + j, d = u + m - 1, l = (i - 1) * m + j, r = l + 1;
			int cnt = 0;
			if (c[i][j] == 'R')
				++cnt;
			if (c[i][j + 1] == 'R')
				++cnt;
			if (c[i + 1][j] == 'R')
				++cnt;
			if (c[i + 1][j + 1] == 'R')
				++cnt;
			if (cnt == 0 || cnt == 4)
				continue;
			if (cnt == 1)
			{
				if (c[i][j] == 'R')
					v1[l] = v2[l] = u;
				else if (c[i][j + 1] == 'R')
					v1[u] = v2[u] = r;
				else if (c[i + 1][j + 1] == 'R')
					v1[r] = v2[r] = d;
				else
					v1[d] = v2[d] = l;
				continue;
			}
			if (cnt == 3)
			{
				if (c[i][j] == 'B')
					v1[u] = v2[u] = l;
				else if (c[i][j + 1] == 'B')
					v1[r] = v2[r] = u;
				else if (c[i + 1][j + 1] == 'B')
					v1[d] = v2[d] = r;
				else
					v1[l] = v2[l] = d;
				continue;
			}
			if (c[i][j] == 'R' && c[i + 1][j + 1] == 'R')
				v1[l] = u, v2[l] = d, v1[r] = d, v2[r] = u;
			else if (c[i + 1][j] == 'R' && c[i][j + 1] == 'R')
				v1[u] = r, v2[u] = l, v1[d] = l, v2[d] = r;
			else if (c[i][j] == 'R' && c[i][j + 1] == 'R')
				v1[l] = v2[l] = r;
			else if (c[i][j + 1] == 'R' && c[i + 1][j + 1] == 'R')
				v1[u] = v2[u] = d;
			else if (c[i + 1][j] == 'R' && c[i + 1][j + 1] == 'R')
				v1[r] = v2[r] = l;
			else
				v1[d] = v2[d] = u;
		}
	}
	for (int i = 1; i <= M; ++i)
		if (v1[i])
			++in[v1[i]];
	int k = 0;
	for (int i = 1; i <= M; ++i)
	{
		if (v1[i] && !in[i])
		{
			++k;
			int x = i, c = 0;
			while (x)
				c1[x] = k, n1[x] = ++c, x = v1[x];
		}
	}
	for (int i = 1; i <= M; ++i)
	{
		if (v1[i] && !c1[i])
		{
			++k;
			int x = i, c = 0;
			while (!c1[x])
				c1[x] = k, n1[x] = ++c, x = v1[x];
		}
	}
	k = 0;
	for (int i = 1; i <= M; ++i)
	{
		if (v2[i] && !in[i])
		{
			++k;
			int x = i, c = 0;
			while (x)
				c2[x] = k, n2[x] = ++c, x = v2[x];
		}
	}
	for (int i = 1; i <= M; ++i)
	{
		if (v2[i] && !c2[i])
		{
			++k;
			int x = i, c = 0;
			while (!c2[x])
				c2[x] = k, n2[x] = ++c, x = v2[x];
		}
	}
	for (int U = n; U; --U)
	{
		int u = U + 1;
		for (int l = 1; l <= m; ++l)
		{
			if (c[U][l] == 'B')
				continue;
			int r = nr[U][l];
			int L = l - 1, R = r + 1;
			if (l > 1 && r < m)
			{
				int d = min(nb[U][L], nb[U][R]);
				if (nr[d + 1][l] >= r && sol(U, d + 1, L, R) == 1)
					++ans;
				if (v[l][r].size() > 0 && v[l][r][v[l][r].size() - 1] > d)
				{
					v[l][r].clear();
					l0[l][r] = l1[l][r] = 0;
				}
				v[l][r].pb(U);
				while (sol(U, v[l][r][l0[l][r]], l - 1, r + 1) > 0)
					++l0[l][r];
				while (sol(U, v[l][r][l1[l][r]], l - 1, r + 1) > 1)
					++l1[l][r];
				ans += l0[l][r] - l1[l][r];
			}
			int S = 0;
			for (int i = l; i <= r; ++i)
			{
				int d = nb[u][i];
				if (!d)
					continue;
				int D = d + 1;
				if (nb[U][L] > U)
				{
					for (int j = min(nb[U][L], d) + 1; j > u; --j)
					{
						if (nr[j][l] >= i - 1)
						{
							if (sol(U, j, L, i) == 1)
								++ans;
						}
					}
				}
				if (nb[U][R] > U)
				{
					for (int j = min(nb[U][R], d) + 1; j > u; --j)
					{
						if (nr[j][i + 1] >= r)
						{
							if (sol(U, j, i, R) == 1)
								++ans;
						}
					}
				}
				for (int j = u; j < d; ++j)
				{
					if (!S)
						break;
					if (sd[S] == j)
					{
						if (nr[j + 1][sa[S]] == i - 1)
						{
							int ret = sol(U, j + 1, sa[S], i);
							if (ret == 1)
								ans += 1 + sr[S] + sb[S];
							else if (ret == 2)
								ans += sr[S];
						}
						else if (nr[j + 1][sa[S] + 1] == i - 1)
						{
							if (sol(U, j + 1, sa[S], i) == 1)
								++ans;
						}
						--S;
					}
					else
					{
						if (nr[j + 1][sa[S] + 1] == i - 1)
						{
							if (sol(U, j + 1, sa[S], i) == 1)
								++ans;
						}
					}
				}
				if (S && sd[S] == d)
				{
					if (nr[D][sa[S]] >= i - 1)
					{
						int ret = sol(U, D, sa[S], i);
						if (ret == 0)
							sr[S] = sb[S] = 0;
						else if (ret == 1)
							sr[S] += sb[S] + 1, sb[S] = 0, ans += sr[S];
						else
							ans += sr[S], ++sb[S];
						sa[S] = i;
					}
					else if (nr[D][sa[S] + 1] >= i - 1)
					{
						int ret = sol(U, D, sa[S], i);
						if (ret == 1)
							sr[S] = 1, sb[S] = 0, ++ans;
						else
							sr[S] = 0, sb[S] = ret / 2;
						sa[S] = i;
					}
					else
					{
						sa[S] = i;
						sr[S] = 0;
						sb[S] = 0;
					}
				}
				else if (S && nr[D][sa[S] + 1] >= i - 1)
				{
					int ret = sol(U, D, sa[S], i);
					sa[++S] = i;
					sd[S] = d;
					if (ret == 1)
						sr[S] = 1, sb[S] = 0, ++ans;
					else
						sr[S] = 0, sb[S] = ret / 2;
				}
				else
				{
					sd[++S] = d;
					sa[S] = i;
					sr[S] = 0;
					sb[S] = 0;
				}
			}
			l = r + 1;
		}
	}
	printf("%lld\n", ans);
	return 0;
}
