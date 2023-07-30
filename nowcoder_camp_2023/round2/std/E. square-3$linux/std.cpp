#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;
using ll = long long;
const ll P = 1e9;
ll solve()
{
    ll x, ans = -1;
    cin >> x;
    auto check = [&](ll a) -> ll
    {
        ll rt = sqrtl(a);
        for (ll i = max(rt - 5, 0ll); i < rt + 5; i++)
        {
            if (i * i < a)
                continue;
            ll j = i * i;
            while (j > x)
                j /= 10;
            if (j == x)
                return i;
            else
                return -1;
        }
        return -1;
    };
    for (ll a = x * P; a >= x; a /= 10)
    {
        ans = max(ans, check(a));
        if (ans > -1)
            return ans;
    }
    return -1;
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int t = 1;
    cin >> t;
    while (t--)
        cout << solve() << endl;
    return 0;
}
