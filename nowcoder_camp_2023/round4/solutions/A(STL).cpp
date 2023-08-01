#include <bits/stdc++.h>
using namespace std;
using LL = long long;

void solve()
{
    int n; cin >> n;
    string t; cin >> t;
    string s1(n, '1'), s0(n, '0');
    auto check = [&](string s)
    {
        string a = t.substr(1) + s + t.substr(0, t.size() - 1);
        if (a.find(t) != -1) return false;
        return true;
    };
    if (check(s1)) cout << s1 << endl;
    else cout << s0 << endl;
}

signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int T = 1; cin >> T;
    while (T--) solve();
    return 0;
}