#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int N = 3e5 + 100;
const int C = 20;
const int L = 9;

int fr[L][C][N], to[L][C][N];
int digits[N];
int q[N], ql, qr;
int ans;

void pre()
{
	for (int i = 0; i < N; i++)
		for (int v = i; v; v /= 10)
			digits[i] |= 1 << (v % 10);
}

void bfs(int *fd, int *td, int s, int l, int r)
{
	ql = qr = 0;
	td[s] = 0;
	q[qr++] = s;
	while (ql < qr)
	{
		int cur, tar;
		cur = q[ql];
		for (int v = cur; v; v /= 10)
		{
			tar = cur + v % 10;
			if (tar <= r && td[tar] == -1)
			{
				td[tar] = td[cur] + 1;
				q[qr++] = tar;
			}
			tar = cur - v % 10;
			if (tar >= l && td[tar] == -1)
			{
				td[tar] = td[cur] + 1;
				q[qr++] = tar;
			}
		}
		ql++;
	}
	ql = qr = 0;
	fd[s] = 0;
	q[qr++] = s;
	while (ql < qr)
	{
		int cur, tar;
		cur = q[ql];
		for (int v = 0; v < 10; v++)
		{
			tar = cur + v;
			if (tar <= r && (digits[tar] & (1 << v)) && fd[tar] == -1)
			{
				fd[tar] = fd[cur] + 1;
				q[qr++] = tar;
			}
			tar = cur - v;
			if (tar >= l && (digits[tar] & (1 << v)) && fd[tar] == -1)
			{
				fd[tar] = fd[cur] + 1;
				q[qr++] = tar;
			}
		}
		ql++;
	}
}

void build(int l, int r, int d = 0)
{
	int ml = (l + r) / 2 - 3, mr = ml + 8;
	ml = max(ml, l);
	mr = min(mr, r);
	for (int i = ml; i <= mr; i++)
		bfs(fr[i - ml][d], to[i - ml][d], i, l, r);
	if (l < ml)
		build(l, ml - 1, d + 1);
	if (mr < r)
		build(mr + 1, r, d + 1);
}

int query(int x, int y, int l = 0, int r = N - 1, int d = 0)
{
	int cur = -1;
	int ml = (l + r) / 2 - 3, mr = ml + 8;
	ml = max(ml, l);
	mr = min(mr, r);
	for (int i = ml; i <= mr; i++)
	{
		if (fr[i - ml][d][x] == -1 || to[i - ml][d][y] == -1)
			continue;
		int len = fr[i - ml][d][x] + to[i - ml][d][y];
		if (cur == -1 || len < cur)
			cur = len;
	}
	int len = -1;
	if (x < ml && y < ml)
		len = query(x, y, l, ml - 1, d + 1);
	if (mr < x && mr < y)
		len = query(x, y, mr + 1, r, d + 1);
	if (len != -1 && (cur == -1 || len < cur))
		cur = len;
	return cur;
}

int main()
{
	pre();
	memset(fr, -1, sizeof(fr));
	memset(to, -1, sizeof(to));
	build(0, N - 1);

	int T;
	scanf("%d", &T);
	while (T--)
	{
		int x, y;
		scanf("%d%d", &x, &y);
		x ^= ans + 1;
		y ^= ans + 1;
		ans = query(x, y);
		printf("%d\n", ans);
	}

	return 0;
}