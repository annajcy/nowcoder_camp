#include <bits/stdc++.h>
#define ll long long
#define pb emplace_back
#define mp make_pair
#define orz 1000000007
#define fi first
#define se second
using namespace std;
int n, m, q, la[2000005];
ll ans;
char c1[10], c2[5];
int a[1000005];
int main()
{
	scanf("%d%d%d", &n, &m, &q);
	for (int i = 1; i <= q; ++i)
	{
		int x;
		scanf("%s%d%s", c1, &x, c2);
		if (c1[0] == 'r')
			a[i] |= 2, x += m;
		if (c2[1] == 'n')
			a[i] |= 1;
		a[la[x]] = -1, la[x] = i;
	}
	for (int i = q; i; --i)
	{
		if (a[i] == -1)
			continue;
		if (a[i] & 2)
		{
			if (a[i] & 1)
				ans += m;
			--n;
		}
		else
		{
			if (a[i] & 1)
				ans += n;
			--m;
		}
	}
	printf("%lld\n", ans);
	return 0;
}
