#include <cstdio>
#include <algorithm>
#include <functional>
#include <queue>
#include <vector>

using std::function;
using std::min;
using std::queue;
using std::swap;
using std::vector;

using ll = long long;
const int inf = 0x3f3f3f3f;

int debugcnt = 0;

struct ZzqFlow
{
	struct Edge
	{
		int to, f;
	};
	int n, S, T;
	vector<Edge> edge;
	vector<vector<int>> eid;
	vector<int> dis, gap, cur;
	ZzqFlow(int _n, int _S, int _T) : n(_n), S(_S), T(_T), eid(n) {}
	void addEdge(int u, int v, int f)
	{
		eid[u].emplace_back(edge.size());
		edge.push_back({v, f});
		eid[v].emplace_back(edge.size());
		edge.push_back({u, 0});
		//		printf("add %d %d %d\n",u,v,f);
		debugcnt++;
	}
	void bfs()
	{
		dis.assign(n, inf);
		queue<int> que;
		que.push(T), dis[T] = 0;
		while (!que.empty())
		{
			int v = que.front();
			que.pop();
			for (auto i : eid[v])
			{
				int u = edge[i].to, f = edge[i ^ 1].f;
				if (f > 0 && dis[u] > dis[v] + 1)
				{
					dis[u] = dis[v] + 1;
					que.push(u);
				}
			}
		}
		if (dis[S] >= inf)
		{
			return;
		}
		gap.assign(n + 2, 0);
		for (int i = 0; i < n; i++)
		{
			if (dis[i] <= n)
			{
				++gap[dis[i]];
			}
		}
		cur.assign(n, 0);
	}
	int isap(int v, int flow)
	{
		if (v == T)
		{
			return flow;
		}
		int ref = flow;
		for (int &i = cur[v]; i < (int)eid[v].size(); i++)
		{
			int id = eid[v][i];
			int u = edge[id].to;
			int f = edge[id].f;
			if (dis[u] == dis[v] - 1 && f > 0)
			{
				int fl = isap(u, min(ref, f));
				ref -= fl, edge[id].f -= fl, edge[id ^ 1].f += fl;
				if (ref == 0 || dis[S] > n)
				{
					return flow - ref;
				}
			}
		}
		if (!--gap[dis[v]++])
		{
			dis[S] = n + 1;
		}
		else
		{
			cur[v] = 0, ++gap[dis[v]];
		}
		return flow - ref;
	}
	int work()
	{
		int ans = 0;
		for (bfs(); dis[S] <= n; ans += isap(S, inf))
			;
		return ans;
	}
};

struct Tree
{
	struct Cedge
	{
		int to;
		int c;
	};
	struct Node
	{
		vector<Cedge> e;
		int fa, mdep, dep;
		int tp, sn, dfn;
	};

	vector<Node> nodes;

	Tree(int n) : nodes(n + 1)
	{
	}

	void addEdge(int u, int v, int c)
	{
		nodes[u].e.push_back({v, c});
		nodes[v].e.push_back({u, c});
	}

	int dfc;

	void doHld()
	{
		nodes[1].dep = 1;
		nodes[1].fa = -1;
		dfsSz(1);
		dfc = 0;
		nodes[1].tp = 1;
		dfsTp(1);
	}

	void dfsSz(int u)
	{
		int &mdep = nodes[u].mdep;
		int &sn = nodes[u].sn;
		mdep = 1;
		sn = -1;
		for (auto ce : nodes[u].e)
		{
			int v = ce.to;
			if (v == nodes[u].fa)
				continue;
			nodes[v].dep = nodes[u].dep + 1;
			nodes[v].fa = u;
			dfsSz(v);
			if (sn == -1 || nodes[v].mdep > nodes[sn].mdep)
			{
				sn = v;
				mdep = nodes[v].mdep + 1;
			}
		}
	}

	void dfsTp(int u)
	{
		nodes[u].dfn = ++dfc;
		if (nodes[u].sn != -1)
		{
			nodes[nodes[u].sn].tp = nodes[u].tp;
			dfsTp(nodes[u].sn);
		}
		for (auto ce : nodes[u].e)
		{
			int v = ce.to;
			if (v == nodes[u].fa)
				continue;
			if (v == nodes[u].sn)
				continue;
			nodes[v].tp = v;
			dfsTp(v);
		}
	}
};

int main()
{
	int n, m;
	scanf("%d%d", &n, &m);
	Tree t(n);
	int start = 6 * n + m + 1;
	int termi = 6 * n + m + 2;
	ZzqFlow fg(6 * n + m + 3, start, termi);
	auto en = [n](int u)
	{
		return u;
	};
	auto pn = [n](int u)
	{
		return u + n;
	};
	auto tn = [n](int u)
	{
		return u + 2 * n;
	};
	auto qn = [n](int u)
	{
		return u + 6 * n;
	};
	for (int i = 2; i <= n; i++)
	{
		int u, v, c;
		scanf("%d%d%d", &u, &v, &c);
		t.addEdge(u, v, c);
	}
	t.doHld();
	for (int i = 1; i <= n; i++)
	{
		for (auto ce : t.nodes[i].e)
		{
			int v = ce.to;
			if (v == t.nodes[i].fa)
			{
				fg.addEdge(en(i), termi, ce.c);
				break;
			}
		}
		fg.addEdge(pn(i), en(i), inf);
		if (t.nodes[i].tp != i)
		{
			fg.addEdge(pn(i), pn(t.nodes[i].fa), inf);
		}
	}
	vector<int> adfn(n + 1);
	for (int i = 1; i <= n; i++)
	{
		adfn[t.nodes[i].dfn] = i;
	}
	function<void(int, int, int)> buildSegT = [&](int k, int l, int r) -> void
	{
		if (l == r)
		{
			fg.addEdge(tn(k), en(adfn[l]), inf);
			return;
		}
		int mid = (l + r) >> 1;
		fg.addEdge(tn(k), tn(k << 1), inf);
		fg.addEdge(tn(k), tn(k << 1 | 1), inf);
		buildSegT(k << 1, l, mid);
		buildSegT(k << 1 | 1, mid + 1, r);
	};
	function<void(int, int, int, int, int, int)> addSegT = [&](int qn, int k, int l, int r, int L, int R) -> void
	{
		//		printf("ast %d %d %d %d %d %d\n",qn,k,l,r,L,R);
		if (L > R)
			return;
		if (l == L && r == R)
		{
			fg.addEdge(qn, tn(k), inf);
			return;
		}
		int mid = (l + r) >> 1;
		if (R <= mid)
			addSegT(qn, k << 1, l, mid, L, R);
		else if (L > mid)
			addSegT(qn, k << 1 | 1, mid + 1, r, L, R);
		else
			addSegT(qn, k << 1, l, mid, L, mid), addSegT(qn, k << 1 | 1, mid + 1, r, mid + 1, R);
	};
	buildSegT(1, 1, n);
	int ans = 0;
	for (int i = 1; i <= m; i++)
	{
		int u, v, x, y;
		scanf("%d%d%d%d", &u, &v, &x, &y);
		x -= y;
		if (x <= 0)
			continue;
		ans += x;
		fg.addEdge(start, qn(i), x);
		while (true)
		{
			if (t.nodes[u].tp == t.nodes[v].tp)
				break;
			if (t.nodes[t.nodes[u].tp].dep < t.nodes[t.nodes[v].tp].dep)
			{
				swap(u, v);
			}
			//			fg.addEdge(qn(i),pn(u),inf);
			addSegT(qn(i), 1, 1, n, t.nodes[t.nodes[u].tp].dfn, t.nodes[u].dfn);
			u = t.nodes[t.nodes[u].tp].fa;
			//			printf("move u to %d\n",u);
		}
		if (t.nodes[u].dep > t.nodes[v].dep)
		{
			swap(u, v);
		}
		addSegT(qn(i), 1, 1, n, t.nodes[u].dfn + 1, t.nodes[v].dfn);
	}
	ans -= fg.work();
	printf("%d\n", ans);
	// fprintf(stderr,"%d\n",debugcnt);
	return 0;
}
