#include <cstdio>
#include <algorithm>

using namespace std;

const int N = 5e5 + 5;
const int E = N << 1;
const int C = 19;

int n, q;
unsigned long long col[N];
unsigned long long rem[C][N];
int par[C][N], tar[C][N], dep[N];
int h[N], nx[E], to[E], et;

void ae(int u, int v)
{
	et++;
	to[et] = v;
	nx[et] = h[u];
	h[u] = et;
}

void dfs(int u, int p = 0)
{
	dep[u] = dep[p] + 1;
	par[0][u] = p;
	rem[0][u] = col[u] & col[p];
	for (int i = 1; i < C; i++)
	{
		par[i][u] = par[i - 1][par[i - 1][u]];
		rem[i][u] = rem[i - 1][u] & rem[i - 1][par[i - 1][u]];
	}
	int t = u;
	unsigned long long r = rem[0][u];
	for (int i = C - 1; i >= 0; i--)
		if (rem[i][t] & r)
		{
			r &= rem[i][t];
			t = par[i][t];
		}
	if (t == u)
		t = 0;
	tar[0][u] = t;
	for (int i = 1; i < C; i++)
		tar[i][u] = tar[i - 1][tar[i - 1][u]];
	for (int i = h[u]; i; i = nx[i])
		if (to[i] != p)
			dfs(to[i], u);
}

int lca(int u, int v)
{
	if (dep[u] < dep[v])
		swap(u, v);
	for (int i = C - 1; i >= 0; i--)
		if (dep[par[i][u]] >= dep[v])
			u = par[i][u];
	if (u == v)
		return v;
	for (int i = C - 1; i >= 0; i--)
		if (par[i][u] != par[i][v])
		{
			u = par[i][u];
			v = par[i][v];
		}
	return par[0][u];
}

int main()
{
	scanf("%d%d", &n, &q);
	for (int i = 1; i <= n; i++)
		scanf("%llu", &col[i]);
	for (int i = 1; i < n; i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		ae(u, v);
		ae(v, u);
	}
	dfs(1);
	while (q--)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		int l = lca(u, v);
		int cntu = 0, cntv = 0;
		int taru = u, tarv = v;
		for (int i = C - 1; i >= 0; i--)
		{
			if (dep[tar[i][taru]] > dep[l])
			{
				cntu += (1 << i);
				taru = tar[i][taru];
			}
			if (dep[tar[i][tarv]] > dep[l])
			{
				cntv += (1 << i);
				tarv = tar[i][tarv];
			}
		}
		unsigned long long colu = col[taru], colv = col[tarv];
		for (int i = C - 1; i >= 0; i--)
		{
			if (dep[par[i][taru]] >= dep[l])
			{
				colu &= rem[i][taru];
				taru = par[i][taru];
			}
			if (dep[par[i][tarv]] >= dep[l])
			{
				colv &= rem[i][tarv];
				tarv = par[i][tarv];
			}
		}
		if (colu == 0 || colv == 0)
		{
			printf("-1\n");
			continue;
		}
		int ans = cntu + cntv;
		if ((colu & colv) == 0)
			ans++;
		ans += dep[u] + dep[v] - 2 * dep[l];
		printf("%d\n", ans);
	}
	return 0;
}