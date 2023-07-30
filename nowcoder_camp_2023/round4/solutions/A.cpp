#include <bits/stdc++.h>
#define endl '\n'
using namespace std;

void solve()
{
    int n;
    string t;
    cin >> n >> t;
    string s0(n, '0'), s1(n, '1');
    s0 = t + s0 + t, s1 = t + s1 + t;

    auto get_next = [&](string s)
    {
        int n = s.size();
        s = '.' + s;
        vector<int> ne(n + 1);
        ne[1] = 0;
        for (int i = 2; i <= n; i++)
        {
            ne[i] = ne[i - 1];
            while (ne[i] && s[i] != s[ne[i] + 1])
                ne[i] = ne[ne[i]];
            ne[i] += (s[i] == s[ne[i] + 1]);
        }
        return ne;
    };

    auto kmp = [&](string s, string t, const vector<int> &ne)
    {
        int n = s.size();
        s = '.' + s;
        int m = t.size();
        t = '.' + t;
        int res = 0;
        for (int i = 1, j = 0; i <= n; i++)
        {
            while (j && s[i] != t[j + 1])
                j = ne[j];
            if (s[i] == t[j + 1])
                j++;
            if (j == m)
                res++, j = ne[j];
        }
        return res;
    };

    vector<int> ne = get_next(t);
    if (kmp(s0, t, ne) == 2)
        cout << string(n, '0') << endl;
    else
        cout << string(n, '1') << endl;
}

signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int T = 1;
    cin >> T;
    while (T--)
        solve();
    return 0;
}