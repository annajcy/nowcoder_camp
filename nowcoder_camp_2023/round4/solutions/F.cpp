#include <bits/stdc++.h>
using namespace std;
using PII = pair<int, int>;

int find(const vector<PII> &q, int l, int r, int v)
{
    while (l < r)
    {
        int mid = (l + r) >> 1;
        if (q[mid].first > v)
            r = mid;
        else
            l = mid + 1;
    }
    return l;
}

void solve()
{
    int n;
    cin >> n;
    vector<PII> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i].first, a[i].second = i + 1;
    sort(a.begin(), a.end());
    int l = 0, r = n - 1;
    while (l < r)
    {
        int mid_v = (a[l].first + a[r].first) >> 1;
        int mid = find(a, l, r, mid_v);
        if (r - mid + 1 <= mid - l)
            r--;
        else
            l++;
    }
    cout << a[l].second << endl;
}

signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int T = 1; // cin >> T;
    while (T--)
        solve();
    return 0;
}