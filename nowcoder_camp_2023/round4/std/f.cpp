#include <bits/stdc++.h>
#define ll long long
#define pb emplace_back
#define mp make_pair
#define orz 1000000007
#define fi first
#define se second
using namespace std;
int n;
pair<int, int> p[1000005];
int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i)
		scanf("%d", &p[i].fi), p[i].se = i;
	sort(p + 1, p + n + 1);
	int l = 1, r = n;
	while (r > l)
	{
		int m = (l + r) / 2;
		if (p[r].fi - p[m].fi >= p[m].fi - p[l].fi)
			--r;
		else
			++l;
	}
	printf("%d\n", p[l].se);
	return 0;
}