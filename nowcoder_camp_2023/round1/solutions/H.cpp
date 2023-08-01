#include <bits/stdc++.h>
using namespace std;

using LL = long long;
const LL INF = 0x3f3f3f3f3f3f3f3fll;

struct Segment
{
	LL l, r; bool type;
	Segment(LL _l, LL _r) { l = min(_l, _r), r = max(_l, _r), type = _l > _r; }
};

void solve()
{
	int n; cin >> n;
	vector<int> a(n + 1), b(n + 1);
	for (int i = 1; i <= n; i ++) cin >> a[i];
	for (int i = 1; i <= n; i ++) cin >> b[i];
	vector<Segment> segs;
	LL sum = 0;
	for (int i = 1; i <= n; i ++)
	{
		sum += abs(a[i] - b[i]);
		segs.emplace_back(a[i], b[i]);
	}
	sort(segs.begin(), segs.end(), [&](Segment s1, Segment s2){
		return s1.r > s2.r;
	});
	LL res = 0, l[2] = {INF, INF};
	for (int i = 0; i < n; i ++)
	{
		if (l[!segs[i].type] < segs[i].r) res = max(res, segs[i].r - max(segs[i].l, l[!segs[i].type]));
		l[segs[i].type] = min(l[segs[i].type], segs[i].l);
	}
	cout << sum - 2 * res << endl;
}

signed main()
{
	ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
	int T = 1; //cin >> T;
	while (T --) solve();
	return 0;
}