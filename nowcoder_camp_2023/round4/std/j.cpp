#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 5e3 + 5;
const int M = 998244353;
int dp[maxn][maxn];
int n, m, inv[maxn], p[maxn], np[maxn];
int f[maxn], sum[maxn], ans;
void add(int &x, int y)
{
    x += y;
    if (x >= M)
        x -= M;
}
void dec(int &x, int y)
{
    x -= y;
    if (x < 0)
        x += M;
}
int main()
{
    cin >> n >> m;
    inv[1] = 1;
    for (int i = 2; i < maxn; i++)
        inv[i] = 1ll * (M / i) * inv[M % i] % M;
    p[0] = np[0] = 1;
    for (int i = 1; i < maxn; i++)
        p[i] = 1ll * p[i - 1] * (m + 1) % M, np[i] = 1ll * np[i - 1] * inv[m + 1] % M;
    f[0] = 1;
    f[1] = m + 1;
    for (int i = 1; i <= m; i++)
        dp[1][i] = 1;
    for (int i = 2; i <= n; i++)
    {
        int sum = 0, tot = 0;
        for (int j = m; j >= 1; j--)
        {
            dp[i][j] = 1ll * f[i - 2] * (m - j + 1) % M;
            add(dp[i][j], sum);
            add(tot, dp[i - 2][m + 1 - j]);
            add(sum, tot);
        }
        f[i] = 1ll * f[i - 1] * (m + 1) % M;
        for (int j = 1; j <= m; j++)
            add(f[i], 1ll * dp[i - 1][j] * (m + 1 - j) % M);
    }
    ans = f[n];
    for (int i = 1; i <= m; i++)
        add(ans, dp[n][i]);
    cout << ans << endl;
}