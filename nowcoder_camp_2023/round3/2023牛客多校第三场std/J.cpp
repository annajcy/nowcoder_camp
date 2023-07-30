#include <cstdio>
#include <algorithm>

using namespace std;

const int N = 1e6 + 5;

int n, m;
int h[N], nx[N], to[N];
int indeg[N];
int q[N], ql, qr;

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		to[i] = v;
		nx[i] = h[u];
		h[u] = i;
		indeg[v]++;
	}
	for (int i = 1; i <= n; i++)
		if (!indeg[i])
			q[++qr] = i;
	ql = 1;
	while (ql <= qr)
	{
		int cur = q[ql];
		for (int i = h[cur]; i; i = nx[i])
		{
			indeg[to[i]]--;
			if (!indeg[to[i]])
				q[++qr] = to[i];
		}
		ql++;
	}
	if (qr == n)
	{
		printf("1\n");
		for (int i = 1; i <= n; i++)
			printf("%d%c", q[i], " \n"[i == n]);
		return 0;
	}
	printf("2\n");
	for (int i = 1; i <= n; i++)
		printf("%d%c", i, " \n"[i == n]);
	for (int i = 1; i <= n; i++)
		printf("%d%c", n - i + 1, " \n"[i == n]);
	return 0;
}