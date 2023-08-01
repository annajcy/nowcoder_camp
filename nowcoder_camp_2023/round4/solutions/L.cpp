#include <bits/stdc++.h>
using namespace std;
using LL = long long;

struct query { int type, op, id; };

void solve()
{
	int n, m, q; cin >> n >> m >> q;
	vector<query> queries;

	while (q --)
	{
		string type; cin >> type;
		if (type == "row")
		{
			int id; cin >> id;
			string t; cin >> t;
			if (t == "on") queries.push_back({0, 1, id});
			else queries.push_back({0, 0, id});
		}
		else
		{
			int id; cin >> id;
			string t; cin >> t;
			if (t == "on") queries.push_back({1, 1, id});
			else queries.push_back({1, 0, id});
		}
	}

	reverse(queries.begin(), queries.end());
	unordered_set<int> row_id, col_id;
	int row_cnt = 0, col_cnt = 0;
	LL res = 0;
	for (auto &[type, op, id] : queries)
		if (type == 0)
		{
			if (row_id.count(id)) continue;
			row_id.insert(id), row_cnt ++;
			if (op == 1) res += m - col_cnt;
		}
		else
		{
			if (col_id.count(id)) continue;
			col_id.insert(id), col_cnt ++;
			if (op == 1) res += n - row_cnt;
		}

	cout << res << endl;
}

signed main()
{
	ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
	int T = 1; //cin >> T;
	while (T --) solve();
	return 0;
}