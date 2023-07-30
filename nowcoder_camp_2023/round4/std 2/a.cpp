#include <bits/stdc++.h>
#define ll long long
#define pb emplace_back
#define mp make_pair
#define orz 1000000007
#define fi first
#define se second
#pragma GCC optmize("O2")
#define S 1048576
using namespace std;
mt19937 rnd(0);
char I[S + 1], *Is = I, *It = I;
inline char gc() { return Is == It ? ((It = (Is = I) + fread(I, 1, S, stdin)) == I ? EOF : *Is++) : *Is++; }
int get()
{
	int x = 0;
	char c = gc();
	while (c < 48)
		c = gc();
	while (c > 47)
		x = x * 10 + c - 48, c = gc();
	return x;
}
int T, n, m, z[3005], f[1005];
int c[1005], ans[1005], c2[3005];
bool chk()
{
	for (int i = 1; i <= m; ++i)
		c2[i] = c2[n + m + i] = c[i];
	for (int i = 1; i <= n; ++i)
		c2[m + i] = ans[i];
	int N = m + n + m;
	int k = 0;
	z[1] = N;
	c2[N + 1] = -1;
	for (int i = 2; i <= m + n; ++i)
	{
		if (i < k + z[k])
			z[i] = min(k + z[k] - i, z[i - k + 1]);
		else
			z[i] = 0;
		while (c2[i + z[i]] == c2[1 + z[i]])
			++z[i];
		if (i + z[i] > k + z[k])
			k = i;
		if (z[i] >= m)
			return 0;
	}
	return 1;
}
void prt()
{
	for (int i = 1; i <= n; ++i)
		printf("%c", 48 + ans[i]);
	printf("\n");
}
int main()
{
	T = get();
	while (T--)
	{
		n = get();
		char _ = gc();
		while (_ < 48)
			_ = gc();
		m = 0;
		while (_ > 47)
			c[++m] = _ - 48, _ = gc();
		bool ok = 1;
		for (int i = 2; i <= m; ++i)
			if (c[i] != c[i - 1])
				ok = 0;
		if (ok || (n + 1) >= m)
		{
			if (c[1])
			{
				for (int i = 1; i <= n; ++i)
					printf("0");
			}
			else
			{
				for (int i = 1; i <= n; ++i)
					printf("1");
			}
			printf("\n");
			continue;
		}
		while (1)
		{
			for (int i = 1; i <= n; ++i)
				ans[i] = rnd() & 1;
			if (chk())
			{
				prt();
				break;
			}
		}
	}
	return 0;
}
