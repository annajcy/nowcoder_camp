#include <bits/stdc++.h>

using LL = long long;
using ld = long double;
using Pair = std::pair<int, int>;
#define inf 1'000'000'000'000'000ll
std::mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());

inline void solve()
{
    int n;
    std::cin >> n;
    std::vector<int> a(n), b(n);
    for (auto &x : a)
        std::cin >> x;
    for (auto &x : b)
        std::cin >> x;
    std::array<std::array<LL, 3>, 2> f{};
    if (b[0])
        f[1][0] = a[0], f[1][1] = f[0][0] = -inf, f[0][1] = 0, f[1][2] = -inf;
    else
        f[0][0] = 0, f[1][0] = f[1][1] = f[0][1] = f[1][2] = -inf;
    for (int i = 1; i < n; i++)
    {
        auto g = f;
        if (b[i])
        {
            f[0][0] = g[0][0] + a[i - 1];
            f[0][1] = std::max({g[0][0], g[1][0], g[1][1]});
            f[1][0] = std::max({g[0][0], g[1][0], g[1][1]}) + a[i];
            f[1][1] = -inf;
            f[1][2] = std::max(g[0][1], g[1][2]) + a[i];
        }
        else
        {
            f[0][0] = std::max({g[0][0], g[1][0], g[1][1]});
            f[0][1] = -inf;
            f[1][0] = -inf;
            f[1][1] = std::max(g[0][1], g[1][2]) + a[i];
            f[1][2] = -inf;
        }
    }
    LL ans = std::max({f[0][0], f[0][1], f[1][0], f[1][1], f[1][2]});
    std::cout << ans << '\n';
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    int T = 1;
    while (T--)
        solve();
    return 0;
}
