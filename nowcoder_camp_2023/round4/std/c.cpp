#include <bits/stdc++.h>
#define pb push_back
using namespace std;
typedef double db;
typedef long long ll;
const db pi = acos(-1.0);
const ll inf = 1e13;
ll ans, sc[1005];
db r, r1, R, X, Y;
db x[1005], y[1005];
int n;
struct node
{
    db a;
    ll sc;
};
bool cmp(node u, node v)
{
    return u.a < v.a;
}
db sqr(db x) { return x * x; }
vector<node> events;
ll all_e;
db f(db x)
{
    while (x >= pi)
        x -= pi * 2;
    while (x < pi)
        x += pi * 2;
    return x;
}
void add_event(db l, db r, ll val)
{
    l = f(l);
    r = f(r);
    if (l < r)
    {
        events.pb((node){l, val});
        events.pb((node){r, -val});
    }
    else
    {
        all_e += val;
        events.pb((node){r, -val});
        events.pb((node){l, +val});
    }
}
int main()
{
    cin >> n >> r1 >> r >> R >> X >> Y;
    r += r1;
    for (int i = 0; i < n; i++)
        cin >> sc[i];
    for (int i = 0; i < n; i++)
        cin >> x[i] >> y[i];
    ll ans = 0;
    for (int i = 0; i < n; i++)
    {
        db d = sqrt(sqr(x[i] - X) + sqr(y[i] - Y));
        if (d <= R)
            ans += sc[i];
    }
    for (int i = 0; i < n; i++)
    {
        events.clear();
        all_e = max(0ll, sc[i]);
        for (int j = 0; j < n; j++)
        {
            if (i == j)
                continue;
            db d = sqrt(sqr(x[i] - x[j]) + sqr(y[i] - y[j]));
            if (d > R * 2)
                continue;
            db k = atan2(x[j] - x[i], y[j] - y[i]);
            db rad = acos(d / (2 * R));
            add_event(k - rad, k + rad, sc[j]);
        }
        db d = sqrt(sqr(x[i] - X) + sqr(y[i] - Y));
        if (d > r + R || r + d < R)
            continue;
        else if (d + R > r)
        {
            db k = atan2(X - x[i], Y - y[i]);
            db rad = acos((R * R + d * d - r * r) / (2 * R * d));
            all_e -= inf;
            add_event(k - rad, k + rad, inf);
        }
        sort(events.begin(), events.end(), cmp);
        ans = max(ans, all_e);
        for (auto nd : events)
        {
            all_e += nd.sc;
            ans = max(ans, all_e);
        }
    }
    cout << ans << endl;
}