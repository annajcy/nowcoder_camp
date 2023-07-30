#include <bits/stdc++.h>
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pi;
const int M = 998244353;
ll pow_(ll x, ll y)
{
    ll ret = 1;
    while (y)
    {
        if (y & 1)
            ret = ret * x % M;
        x = x * x % M;
        y >>= 1;
    }
    return ret;
}
const int maxn = 1e5 + 3;
ll inv(ll x) { return pow_(x, M - 2); }
ll x, y, d, p, ans, pw[maxn];
string S = "";
int u;
map<pi, int> g;
void f(ll &x, ll &y)
{
    if (x >= y && (x - 1) / d == (y - 1) / d)
    {
        x = (x - 1) % d + 1;
        y = (y - 1) % d + 1;
    }
    if (x <= d || x < y)
    {
        x = x * 2;
        S += (char)(u + '0');
    }
    else
        x = x - d;
}
void solve()
{
    cin >> x >> y >> d >> p;
    p = p * inv(100) % M;
    int last, lsz = 0;
    S = "";
    g.clear();
    g[(pi){x, y}] = 0;
    while (1)
    {
        u = 0;
        f(x, y);
        u = 1;
        f(y, x);
        if (x >= 4 * d && y >= 4 * d && S.size() == lsz + 2)
        {
            last = lsz;
            break;
        }
        if (g.find((pi){x, y}) != g.end())
        {
            last = g[(pi){x, y}];
            break;
        }
        g[(pi){x, y}] = S.size();
        lsz = S.size();
    }
    pw[0] = 1;
    for (int i = 1; i <= (int)S.size(); i++)
        pw[i] = pw[i - 1] * p % M;
    ans = 0;
    for (int i = 0; i < last; i++)
        if (S[i] == '1')
            ans = (ans + pw[i] * (1 + M - p) % M);
    ll s = 0, t = 0;
    for (int i = 0; i < (int)S.size() - last; i++)
    {
        s = (s + pw[i]) % M;
        if (S[i + last] == '1')
            t = (t + pw[i]) % M;
    }
    ans = (ans + pw[last] * t % M * inv(s)) % M;
    cout << ans << endl;
}
int main()
{
    int T;
    cin >> T;
    while (T--)
        solve();
}