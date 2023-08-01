#include <bits/stdc++.h>
#define MAXN 505
#define INF 1000000000
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<ll, int> P;
int n, k;
int c[MAXN][MAXN];
int from[MAXN][MAXN], to[MAXN][MAXN];
ll d[MAXN][MAXN], ans[MAXN][MAXN];
ll pre[MAXN][MAXN];
int mult[MAXN][MAXN];
namespace IO
{
    const int MX = 4e7; // 1e7占用内存11000kb
    char buf[MX];
    int c, sz;
    void begin()
    {
        c = 0;
        sz = fread(buf, 1, MX, stdin);
    }
    inline bool read(int &t)
    {
        while (c < sz && buf[c] != '-' && (buf[c] < '0' || buf[c] > '9'))
            c++;
        if (c >= sz)
            return false;
        bool flag = 0;
        if (buf[c] == '-')
            flag = 1, c++;
        for (t = 0; c < sz && '0' <= buf[c] && buf[c] <= '9'; c++)
            t = t * 10 + buf[c] - '0';
        if (flag)
            t = -t;
        return true;
    }
    inline bool read(ll &t)
    {
        while (c < sz && buf[c] != '-' && (buf[c] < '0' || buf[c] > '9'))
            c++;
        if (c >= sz)
            return false;
        bool flag = 0;
        if (buf[c] == '-')
            flag = 1, c++;
        for (t = 0; c < sz && '0' <= buf[c] && buf[c] <= '9'; c++)
            t = t * 10 + buf[c] - '0';
        if (flag)
            t = -t;
        return true;
    }
}
void floyd_warshall()
{
    for (int k = 1; k <= n; k++)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
}
int main()
{
    IO::begin();
    IO::read(n);
    IO::read(k);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            IO::read(d[i][j]);
    floyd_warshall();
    ll x;
    IO::read(x);
    ll all = 0;
    for (int i = 1; i <= k - 1; i++)
    {
        ll y;
        IO::read(y);
        c[x][y]++;
        all += d[x][y];
        x = y;
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
            from[i][j] = to[i][j] = j;
        sort(from[i] + 1, from[i] + n + 1, [&](int x, int y)
             { return d[i][x] < d[i][y]; });
        sort(to[i] + 1, to[i] + n + 1, [&](int x, int y)
             { return d[x][i] < d[y][i]; });
    }
    for (int s = 1; s <= n; s++)
    {
        memset(pre, 0, sizeof(pre));
        memset(mult, 0, sizeof(mult));
        for (int t = 1; t <= n; t++)
        {
            if (!c[s][t])
                continue;
            int pos = n;
            for (int i = 1; i <= n; i++)
            {
                int v = to[t][i];
                ll need = d[s][t] - d[v][t];
                while (pos > 0 && need <= d[s][from[s][pos]])
                    pos--;
                if (!pos)
                    break;
                pre[v][pos] += c[s][t] * (d[s][t] - d[v][t]);
                mult[v][pos] += c[s][t];
            }
        }
        for (int v = 1; v <= n; v++)
        {
            for (int i = n; i >= 1; i--)
            {
                pre[v][i] += pre[v][i + 1];
                mult[v][i] += mult[v][i + 1];
                ans[from[s][i]][v] -= mult[v][i] * d[s][from[s][i]];
                ans[from[s][i]][v] += pre[v][i];
            }
        }
    }
    ll res = 0;
    for (int u = 1; u <= n; u++)
        for (int v = u + 1; v <= n; v++)
            res = max(res, ans[u][v] + ans[v][u]);
    printf("%lld\n", all - res);
    return 0;
}