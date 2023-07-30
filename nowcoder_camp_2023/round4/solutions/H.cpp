#include <bits/stdc++.h>
#define endl '\n'
using namespace std;
using LL = long long;

struct Node
{
    int x, y, k;
};

void solve()
{
    int n;
    cin >> n;
    vector<Node> ops;

    function<int(int, int)> cost = [&](int a, int b)
    {
        if (!b)
            return 0;
        if (a == b)
            return 1;
        if (a < b)
            swap(a, b);
        return a / b + cost(b, a % b);
    };

    function<void(int, int, int)> dfs_square = [&](int n, int x, int y)
    {
        function<void(int, int, int, int)> dfs_rect = [&](int a, int b, int x, int y)
        {
            if (!a || !b)
                return;
            if (a <= b)
            {
                int i = y;
                for (; i + a <= y + b; i += a)
                    dfs_square(a, x, i);
                dfs_rect(a, b % a, x, i);
            }
            else
            {
                int i = x;
                for (; i + b <= x + a; i += b)
                    dfs_square(b, i, y);
                dfs_rect(a % b, b, i, y);
            }
        };

        if (n == 1)
            return;
        if (n <= 7)
        {
            ops.push_back({x, y, n});
            return;
        }
        for (int k = 1; k <= n / 2; k++)
        {
            if (2 * cost(n - k, k) + 2 > 50)
                continue;
            dfs_square(k, x, y);
            dfs_square(n - k, x + k, y + k);
            dfs_rect(k, n - k, x, y + k);
            dfs_rect(n - k, k, x + k, y);
            ops.push_back({x, y, n});
            return;
        }
    };

    dfs_square(n, 1, 1);

    cout << ops.size() << endl;
    for (auto &[x, y, k] : ops)
        cout << x << ' ' << y << ' ' << k << endl;
}

signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int T = 1; // cin >> T;
    while (T--)
        solve();
    return 0;
}