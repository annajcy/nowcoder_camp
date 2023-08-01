#include <bits/stdc++.h>
#define endl '\n'
using namespace std;

void solve()
{
    int n, k;
    cin >> n >> k;
    vector<int> a(n + 1), cnt(5);
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    int l = 0, r = 0, res = n;
    while (r <= n)
    {
        while (!(cnt[1] && cnt[2] && cnt[3] && cnt[4] >= k))
        {
            r++;
            cnt[a[r]]++;
            if (r > n)
                break;
        }

        while (cnt[1] && cnt[2] && cnt[3] && cnt[4] >= k)
        {
            l++;
            cnt[a[l]]--;
            if (l > r)
                break;
        }
        res = min(res, r - l + 1);
    }
    cout << res << endl;
}

signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int T = 1; // cin >> T;
    while (T--)
        solve();
    return 0;
}