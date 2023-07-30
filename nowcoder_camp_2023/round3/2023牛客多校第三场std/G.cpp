#pragma GCC optimize("Ofast")
#pragma GCC target("popcnt", "sse3", "sse2", "sse", "avx", "sse4", "sse4.1", "sse4.2", "ssse3", "f16c", "fma", "avx2")
#pragma GCC optimize("inline", "fast-math", "unroll-loops")

#include <bits/stdc++.h>

using namespace std;
using LL = long long;

template <typename T>
ostream &operator<<(ostream &os, const vector<T> &vec)
{
    for (auto &&x : vec)
    {
        os << x << ' ';
    }
    return os;
}

template <typename T>
istream &operator>>(istream &is, vector<T> &vec)
{
    for (auto &&x : vec)
    {
        is >> x;
    }
    return is;
}

template <typename T>
void print(const T &t)
{
    cout << t;
}

template <typename T, typename... Args>
void print(const T &t, const Args &...args)
{
    cout << t << ' ';
    print(args...);
}

constexpr int N = 2'010;

int n, m, a[N][N], f[N];

struct Hash
{
    int base, mod, h[4][N][N], pw[N];
    Hash(int _base, int _mod)
    {
        base = _base;
        mod = _mod;
    }
    void init()
    {
        pw[0] = 1;
        for (int i = 1; i <= max(n, m); i++)
        {
            pw[i] = (LL)pw[i - 1] * base % mod;
        }
        for (int i = 1; i <= n; i++)
        {
            h[0][i][m + 1] = 0;
            for (int j = m; j; j--)
            {
                h[0][i][j] = ((LL)h[0][i][j + 1] * base % mod + a[i][j]) % mod;
            }
            h[1][i][0] = 0;
            for (int j = 1; j <= m; j++)
            {
                h[1][i][j] = ((LL)h[1][i][j - 1] * base % mod + a[i][j]) % mod;
            }
        }
        for (int j = 1; j <= m; j++)
        {
            h[2][n + 1][j] = 0;
            for (int i = n; i; i--)
            {
                h[2][i][j] = ((LL)h[2][i + 1][j] * base % mod + a[i][j]) % mod;
            }
            h[3][0][j] = 0;
            for (int i = 1; i <= n; i++)
            {
                h[3][i][j] = ((LL)h[3][i - 1][j] * base % mod + a[i][j]) % mod;
            }
        }
    }
    bool eqx(int x1, int x2, int l, int r)
    {
        int v1 = (h[0][x1][l] - (LL)h[0][x1][r + 1] * pw[r - l + 1] % mod + mod) % mod;
        int v2 = (h[1][x2][r] - (LL)h[1][x2][l - 1] * pw[r - l + 1] % mod + mod) % mod;
        //        cout << "eqx " << x1 << ' ' << x2 << ' ' << l << ' ' << r << ' ' << v1 << ' ' << v2 << '\n';
        return v1 == v2;
    }
    bool eqy(int y1, int y2, int l, int r)
    {
        int v1 = (h[2][l][y1] - (LL)h[2][r + 1][y1] * pw[r - l + 1] % mod + mod) % mod;
        int v2 = (h[3][r][y2] - (LL)h[3][l - 1][y2] * pw[r - l + 1] % mod + mod) % mod;
        //        cout << "eqy " << y1 << ' ' << y2 << ' ' << l << ' ' << r << ' ' << v1 << ' ' << v2 << '\n';
        return v1 == v2;
    }
} h1(131, 998'244'353), h2(13331, 1e9 + 7);

int main()
{
    //    freopen("in", "r", stdin);
    //    freopen("out", "w", stdout);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
    {
        string s;
        cin >> s;
        for (int j = 1; j <= m; j++)
        {
            a[i][j] = s[j - 1] - 'a';
        }
    }
    h1.init();
    h2.init();
    LL ans = 0;
    for (int i = 1; i <= n; i++)
    {
        ans++;
        int u = 1;
        f[u] = 1;
        for (int j = 2; j <= m; j++)
        {
            f[j] = 1;
            if (u + f[u] - 1 >= j)
            {
                f[j] = min(f[u * 2 - j], u + f[u] - j);
            }
            while (j >= f[j] + 1 && m - j + 1 >= f[j] + 1 && i >= f[j] + 1 && n - i + 1 >= f[j] + 1 &&
                   h1.eqx(i - f[j], i + f[j], j - f[j], j + f[j]) && h2.eqx(i - f[j], i + f[j], j - f[j], j + f[j]) &&
                   h1.eqy(j - f[j], j + f[j], i - f[j], i + f[j]) && h2.eqy(j - f[j], j + f[j], i - f[j], i + f[j]))
            {
                f[j]++;
            }
            ans += f[j];
            if (j + f[j] > u + f[u])
            {
                u = j;
            }
        }
    }
    for (int i = 1; i < n; i++)
    {
        int u = -1;
        for (int j = 1; j < m; j++)
        {
            f[j] = 0;
            if (u != -1 && u + f[u] - 1 >= j)
            {
                f[j] = min(f[u * 2 - j], u + f[u] - j);
            }
            while (j >= f[j] + 1 && m - j >= f[j] + 1 && i >= f[j] + 1 && n - i >= f[j] + 1 &&
                   h1.eqx(i - f[j], i + f[j] + 1, j - f[j], j + f[j] + 1) && h2.eqx(i - f[j], i + f[j] + 1, j - f[j], j + f[j] + 1) &&
                   h1.eqy(j - f[j], j + f[j] + 1, i - f[j], i + f[j] + 1) && h2.eqy(j - f[j], j + f[j] + 1, i - f[j], i + f[j] + 1))
            {
                f[j]++;
            }
            ans += f[j];
            if (u == -1 || j + f[j] > u + f[u])
            {
                u = j;
            }
        }
    }
    cout << ans << '\n';
    return 0;
}