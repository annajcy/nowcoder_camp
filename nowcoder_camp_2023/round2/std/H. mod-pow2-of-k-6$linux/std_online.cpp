#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, n) for (int i = a; i <= n; i++)
#define per(i, a, n) for (int i = n; i >= a; i--)
#define pb push_back
#define SZ(v) ((int)v.size())
#define fs first
#define sc second
typedef long long ll;
typedef double db;
typedef pair<int, int> pii;
int n, q, pre[200010], cntA[200010];
char s[200010], x[60];
int main()
{
	cin >> n >> q;
	scanf("%s", s + 1);
	rep(i, 1, n)
	{
		if (s[i] == 'A')
		{
			pre[i] = -pre[i - 1] - 1;
			cntA[i] = cntA[i - 1] + 1;
		}
		else
		{
			pre[i] = pre[i - 1] + 1;
			cntA[i] = cntA[i - 1];
		}
	}
	ll lastans = 0;
	rep(_, 1, q)
	{
		ll l, r;
		scanf("%lld%lld%s", &l, &r, x + 1);
		l = (lastans ^ l) % n + 1;
		r = (lastans ^ r) % n + 1;
		if (l > r)
			swap(l, r);
		//		cout<<l<<' '<<r<<endl;
		int k = strlen(x + 1);
		ll xnum = 0;
		rep(i, 1, k)
		{
			xnum = 2ll * xnum + (x[i] - '0');
		}
		ll mod = (1ll << k);
		ll ans = 0;
		if ((cntA[r] - cntA[l - 1]) % 2)
		{
			ans = pre[r] + pre[l - 1];
			xnum = -xnum;
		}
		else
		{
			ans = pre[r] - pre[l - 1];
		}
		ans = ((xnum + ans) % mod + mod) % mod;
		rep(i, 1, k)
		{
			putchar('0' + (bool)(ans & (1ll << (k - i))));
		}
		puts("");
		lastans = ans;
	}
	return 0;
}
