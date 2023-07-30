#include <bits/stdc++.h>
using namespace std;
#define rep(i, j, k) for (i = j; i <= k; ++i)
#define dow(i, j, k) for (i = j; i >= k; --i)
#define pr pair
#define mkp make_pair
#define fi first
#define se second
const int N = 1e2 + 10;
int g[N][N][N], n, m, deg[N];
bool tag[N][N], bel[N][N];
void solve(int stp)
{
    int i, j;
    rep(i, 1, n) deg[i] = 0;
    rep(i, 1, n) if (tag[stp][i]) rep(j, i + 1, n) if (tag[stp][j]) if (g[stp][i][j])
    {
        ++deg[i];
        ++deg[j];
    }
    int slc = -1;
    rep(i, 1, n) if (tag[stp][i] && deg[i] & 1) slc = i;
    if (slc < 0)
    {
        rep(i, 1, n) if (tag[stp][i]) bel[stp][i] = 0;
        return;
    }
    rep(i, 1, n) rep(j, 1, n) g[stp + 1][i][j] = g[stp][i][j];
    rep(i, 1, n) tag[stp + 1][i] = tag[stp][i];
    tag[stp + 1][slc] = 0;
    rep(i, 1, n) if (tag[stp + 1][i] && g[stp][slc][i]) rep(j, i + 1, n) if (tag[stp + 1][j] && g[stp][slc][j])
    {
        g[stp + 1][i][j] ^= 1;
        g[stp + 1][j][i] ^= 1;
    }
    solve(stp + 1);
    int cnt[2];
    cnt[0] = cnt[1] = 0;
    rep(i, 1, n) if (tag[stp][i] && g[stp][slc][i]) cnt[bel[stp + 1][i]]++;
    rep(i, 1, n) bel[stp][i] = bel[stp + 1][i];
    if (cnt[0] & 1)
    {
        bel[stp][slc] = 1; // printf(">>%d %d 1\n",stp,slc);
    }
    else
        bel[stp][slc] = 0; // printf(">>%d %d 0\n",stp,slc);
}
int main()
{ // freopen("1.in","r",stdin);
    scanf("%d%d", &n, &m);
    int i;
    rep(i, 1, m)
    {
        int x, y;
        scanf("%d%d", &x, &y);
        g[1][x][y] ^= 1;
        g[1][y][x] ^= 1;
    }
    rep(i, 1, n) tag[1][i] = 1;
    solve(1);
    rep(i, 1, n) printf("%d ", bel[1][i]);
}
