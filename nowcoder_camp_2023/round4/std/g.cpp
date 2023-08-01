#include <bits/stdc++.h>
using namespace std;
const int limit = 2000000000;
const int M = 998244353;
const int maxn = 100010;
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
int a[maxn], b[maxn], n, m, c[maxn], P, K;
int aa[maxn], bb[maxn], s[1005];
int pow_(int x, int y)
{
    int ret = 1;
    while (y)
    {
        if (y & 1)
            ret = 1ll * ret * x % M;
        x = 1ll * x * x % M;
        y >>= 1;
    }
    return ret;
}
int inv(int x) { return pow_(x, M - 2); }
void upd(int x, int y)
{
    while (x <= K)
        c[x] += y, x += x & (-x);
}
int qry(int x)
{
    int ret = 0;
    while (x)
        ret += c[x], x -= x & (-x);
    return ret;
}
int main()
{
    cin >> n >> m >> P;
    K = min((int)sqrt(limit + 1), P);
    for (int i = 0; i < n; i++)
        cin >> a[i];
    for (int i = 0; i < m; i++)
        cin >> b[i];
    sort(a, a + n);
    sort(b, b + m);
    int ans = 0;
    add(ans, 1ll * n * m * P % M);
    for (int i = 0; i < m; i++)
        b[i]--;
    for (int k = 1; k <= K; k++)
    {
        for (int i = 0; i < n; i++)
        {
            add(ans, 1ll * m * (a[i] / k) % M);
            aa[i] = a[i] % k;
        }
        for (int i = 0; i < m; i++)
        {
            add(ans, 1ll * n * (b[i] / k) % M);
            s[i] = 0;
            bb[i] = b[i] % k;
        }
        int p = m, q = m;
        int L = k * K, R = (limit / P < k) ? limit : k * P;
        for (int i = 0; i < n; i++)
        {
            while (p && b[p - 1] + a[i] >= L)
            {
                p--;
                upd(k - bb[p], 1);
            }
            while (q && b[q - 1] + a[i] >= R)
            {
                q--;
                upd(k - bb[q], -1);
            }
            add(ans, 1ll * (m - q) * P % M);
            dec(ans, 1ll * (m - p) * K % M);
            add(ans, 1ll * (q - p) * (a[i] / k) % M);
            add(ans, qry(aa[i]));
            s[p]++;
            s[q]--;
        }
        for (int i = 0; i < m; i++)
        {
            s[i + 1] += s[i];
            add(ans, 1ll * s[i] * (b[i] / k) % M);
        }
        while (p)
            p--, upd(k - bb[p], 1);
        while (q < m)
            upd(k - bb[q], 1), q++;
        for (int i = 0; i < n; i++)
            add(ans, qry(aa[i]));
        for (int i = 0; i < m; i++)
            upd(k - bb[i], -1);
    }
    cout << 1ll * ans * inv(1ll * m * P % M) % M << endl;
}