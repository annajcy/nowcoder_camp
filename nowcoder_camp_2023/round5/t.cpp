#include <bits/stdc++.h>
#define endl '\n'
using namespace std;

void solve()
{
    int n;
    cin >> n;
    vector<vector<int>> g(n + 1, vector<int>(n + 1));
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            cin >> g[i][j];

    vector<int> match(n + 1);
    vector<bool> st(n + 1);

    function<bool(int)> dfs = [&](int u)
    {
        for (int v = 1; v <= n; v++)
        {
            if (!g[u][v])
                continue;
            if (st[v])
                continue;
            st[v] = true;
            if (!match[v] || dfs(match[v]))
            {
                match[v] = u;
                return true;
            }
        }
        return false;
    };

    auto get_best_match = [&]()
    {
        int res = 0;
        for (int u = 1; u <= n; u++)
        {
            st.clear();
            if (dfs(u))
                res++;
        }
        return res;
    };

    cout << get_best_match() << endl;
};

signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int T = 1; // cin >> T;
    while (T--)
        solve();
    return 0;
}