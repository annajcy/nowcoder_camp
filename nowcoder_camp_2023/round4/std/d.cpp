#include <bits/stdc++.h>
using namespace std;
typedef __int128 ll;
char s[45];
ll n, k;
ll p[125][9];
ll read()
{
    cin >> s;
    int l = strlen(s);
    ll x = 0;
    for (int i = 0; i < l; i++)
        x = x * 10 + (s[i] - '0');
    return x;
}
ll F(ll n, ll k)
{
    if (k == 1)
        return n;
    ll ret = 0;
    while (n)
        ret += n % k, n /= k;
    return ret;
}
const long long N = 1000000000000000000ll;
void print(ll x)
{
    long long s = x / N;
    long long t = x % N;
    if (s > 0)
    {
        printf("%lld%18lld\n", s, t);
    }
    else
    {
        printf("%lld\n", t);
    }
}
void solve()
{
    n = read();
    k = read();
    ll ans = n;
    for (int i = 2; i <= 10000 && i <= k; i++)
        ans = min(ans, F(n, i));
    for (int a = 1; a <= 120; a++)
    {
        for (int b = 0; a + b <= 120; b++)
        {
            if ((n - b) % a)
                continue;
            if ((n - b) / a <= k)
                ans = min(ans, (ll)a + b);
        }
    }
    for (int m = 2; m <= 8; m++)
    {
        for (int a = 1; a <= 120; a++)
            for (int b = 0; a + b <= 120; b++)
            {
                ll L = 0, R = p[a][m];
                while (R - L > 1)
                {
                    ll x = (L + R) / 2;
                    ll cur = 1;
                    for (int j = 0; j < m - 1; j++)
                        cur *= x;
                    cur *= (x * a + b);
                    if (cur < n)
                        L = x;
                    else
                        R = x;
                }
                if (R <= k)
                    ans = min(ans, F(n, R));
            }
    }
    print(ans);
}
int main()
{
    for (int j = 1; j <= 120; j++)
        for (int i = 2; i <= 8; i++)
            p[j][i] = powl(1.1e36 / j, 1.0 / i);
    int _;
    cin >> _;
    while (_--)
        solve();
    return 0;
}