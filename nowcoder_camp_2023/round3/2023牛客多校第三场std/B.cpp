#include <bits/stdc++.h>

using LL = long long;
int mod;
const int N = 666;

void up(int &x, int y)
{
    x += y;
    if (x >= mod)
    {
        x -= mod;
    }
}

int f[N][N][2], C[N][N], fac[N];

void solve()
{
    int n, ans = 0;
    std::cin >> n >> mod;

    for (int i = 0; i <= n; i++)
    {
        for (int j = 0; j <= n; j++)
        {
            f[i][j][0] = f[i][j][1] = 0;
        }
    }
    C[0][0] = 1;
    for (int i = 1; i <= n; i++)
    {
        C[i][0] = 1;
        for (int j = 1; j <= i; j++)
        {
            C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % mod;
        }
    }
    fac[0] = 1;
    for (int i = 1; i <= n * 2; i++)
    {
        fac[i] = (LL)fac[i - 1] * i % mod;
    }

    f[0][0][0] = f[0][0][1] = 1;
    for (int i = 0; i <= n; i++)
    {
        for (int j = 0; j <= n; j++)
        {
            for (int o = 0; o < 2; o++)
            {
                if (f[i][j][o])
                {
                    int r = (!o) ? n - j : n - i;
                    for (int k = 1; k <= r; k++)
                    {
                        if (!o)
                        {
                            up(f[i][j + k][o ^ 1], (LL)f[i][j][o] * C[r][k] % mod);
                        }
                        else
                        {
                            up(f[i + k][j][o ^ 1], (LL)f[i][j][o] * C[r][k] % mod);
                        }
                    }
                    for (int k = 1; k <= r; k++)
                    {
                        up(ans, (LL)f[i][j][o] * (i + j + k) % mod * C[r][k] % mod * (k - 1) % mod * fac[2 * n - i - j - k] % mod);
                    }
                    if (i == n && j == n)
                    {
                        up(ans, (LL)f[i][j][o] * 2LL * n % mod);
                    }
                }
            }
        }
    }
    std::cout << ans << '\n';
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int T;
    std::cin >> T;
    while (T--)
    {
        solve();
    }
    return 0;
}
