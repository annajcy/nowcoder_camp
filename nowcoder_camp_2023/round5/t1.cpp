#include <bits/stdc++.h>
#define endl '\n'
using namespace std;

void solve()
{
    int n;
    cin >> n;
    vector<bool> st(n + 1);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
        {
            int x;
            cin >> x;
            if (x)
                st[j] = true;
        }

    int res = 0;
    for (int i = 1; i <= n; i++)
        if (st[i])
            res++;

    cout << res << endl;
};

signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int T = 1; // cin >> T;
    while (T--)
        solve();
    return 0;
}