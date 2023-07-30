#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>
#include <cmath>
#include <set>
#include <map>

using namespace std;

const int N = 1e5 + 5;
const long double EXTEND = 5e9;

const long double oo = 1e18;
const long double eps = 1e-12;

const long double pi = acosl(-1.0l);

long double radius = 0;

struct Point
{
	long double x, y;

	Point() {}
	Point(long double x, long double y)
	{
		this->x = x;
		this->y = y;
	}

	Point &read()
	{
		scanf("%Lf%Lf", &x, &y);
		return *this;
	}

	long double len() const
	{
		return sqrtl(x * x + y * y);
	}

	Point _norm(long double k = 1) const
	{
		long double l = len();
		if (l == 0 || isinf(k) || isnan(k))
			return Point(0, 0);
		return Point(x / l * k, y / l * k);
	}

	Point norm(long double k = 1) const
	{
		long double m = (fabsl(x) + fabsl(y)) / 2;
		if (m == 0 || isinf(k) || isnan(k))
			return Point(0, 0);
		return Point(x / m, y / m)._norm(k);
	}

	Point rotate(long double arg) const
	{
		long double s = sinl(arg), c = cosl(arg);
		return Point(x * c - y * s, x * s + y * c);
	}
};

typedef Point Vec;

Vec operator+(const Vec &a, const Vec &b)
{
	return Vec(a.x + b.x, a.y + b.y);
}
Vec operator-(const Vec &a, const Vec &b)
{
	return Vec(a.x - b.x, a.y - b.y);
}
long double operator^(const Vec &a, const Vec &b)
{
	return a.x * b.x + a.y * b.y;
}
long double operator*(const Vec &a, const Vec &b)
{
	return a.x * b.y - b.x * a.y;
}
Vec operator*(const Vec &a, long double k)
{
	return Vec(k * a.x, k * a.y);
}
Vec operator*(long double k, const Vec &a)
{
	return Vec(k * a.x, k * a.y);
}
Vec operator/(const Vec &a, long double k)
{
	return Vec(a.x / k, a.y / k);
}

bool operator<(const Vec &a, const Vec &b)
{
	if (a.x != b.x)
		return a.x < b.x;
	return a.y < b.y;
}

typedef vector<Point> Polygon;

struct Graph
{
	vector<Point> v;
	vector<pair<int, int>> e;
	map<pair<int, int>, int> nx;
};

namespace Diagram
{
	int n;
	Polygon *convex;
	vector<int> pre, suf;
	Graph g;
	vector<int> idx, outeridx;
	vector<int> llas, rlas;
	int cnt;

	struct Edge;

	vector<Edge> edges;
	set<Edge> q;

	struct Edge
	{
		int id;
		Point l, r;
		long double len;
		long double langle, rangle;
		long double t, tmax;

		Edge() {}

		Edge(int id)
		{
			this->id = id;
			l = (*convex)[id];
			r = (*convex)[(id + 1) % n];
			t = 0;
		}

		void moveto(long double t)
		{
			t -= this->t;
			Point lnew = l + (r - l).rotate(langle).norm(t / sinl(langle));
			Point rnew = r + (l - r).rotate(-rangle).norm(t / sinl(rangle));
			this->t += t;
			l = lnew;
			r = rnew;
			update();
		}

		void update()
		{
			len = (r - l).len();
			Edge epre = edges[pre[id]], esuf = edges[suf[id]];
			langle = acosl((r - l).norm() ^ (epre.l - epre.r).norm()) / 2;
			rangle = acosl((l - r).norm() ^ (esuf.r - esuf.l).norm()) / 2;
			long double speed = (tanl(pi / 2 - langle) + tanl(pi / 2 - rangle));
			if (isnan(speed) || isinf(speed) || fabsl(speed) > oo)
				tmax = oo;
			else
				tmax = t + len / speed;
		}
	};

	bool operator<(const Edge &x, const Edge &y)
	{
		if (x.tmax != y.tmax)
			return x.tmax < y.tmax;
		return x.id < y.id;
	}

	Graph &build(Polygon &c)
	{
		convex = &c;
		n = c.size();
		pre.resize(n);
		suf.resize(n);
		idx.resize(n);
		outeridx.resize(n);
		llas.resize(n);
		rlas.resize(n);
		cnt = 0;
		for (int i = 0; i < n; i++)
		{
			pre[i] = (i + n - 1) % n;
			suf[i] = (i + 1) % n;
			llas[i] = pre[i];
			rlas[i] = suf[i];
			g.v.emplace_back(c[i]);
			idx[i] = cnt++;
			edges.emplace_back(Edge(i));
		}
		for (int i = 0; i < n; i++)
		{
			long double arg = acosl((c[pre[i]] - c[i]).norm() ^ (c[suf[i]] - c[i]).norm()) / 2;
			g.v.emplace_back(c[i] + (c[pre[i]] - c[i]).rotate(pi - arg).norm(EXTEND));
			outeridx[i] = cnt++;
			g.e.emplace_back(make_pair(idx[i], outeridx[i]));
		}
		for (int i = 0; i < n; i++)
		{
			g.e.emplace_back(make_pair(idx[i], idx[(i + 1) % n]));
			g.e.emplace_back(make_pair(outeridx[i], outeridx[(i + 1) % n]));
			edges[i].update();
			q.insert(edges[i]);
		}

		long double cur = 0;
		for (int i = n; i > 2; i--)
		{
			int id = q.begin()->id;
			q.erase(edges[id]);
			q.erase(edges[pre[id]]);
			q.erase(edges[suf[id]]);

			suf[pre[id]] = suf[id];
			pre[suf[id]] = pre[id];

			cur = edges[id].tmax;
			if (cur < oo)
				radius = cur;
			edges[id].moveto(cur);
			edges[pre[id]].moveto(cur);
			edges[suf[id]].moveto(cur);

			g.v.emplace_back(edges[id].l);
			int cidx = cnt++;

			g.e.emplace_back(make_pair(idx[id], cidx));
			g.nx[make_pair(llas[id], idx[id])] = cidx;
			g.nx[make_pair(cidx, idx[id])] = rlas[id];

			g.e.emplace_back(make_pair(idx[suf[id]], cidx));
			g.nx[make_pair(llas[suf[id]], idx[suf[id]])] = cidx;
			g.nx[make_pair(cidx, idx[suf[id]])] = rlas[suf[id]];

			g.nx[make_pair(idx[suf[id]], cidx)] = idx[id];

			llas[suf[id]] = idx[id];
			rlas[suf[id]] = idx[suf[id]];

			idx[suf[id]] = cidx;

			q.insert(edges[pre[id]]);
			q.insert(edges[suf[id]]);
		}
		int id = q.begin()->id;
		g.e.emplace_back(make_pair(idx[id], idx[suf[id]]));
		g.nx[make_pair(llas[id], idx[id])] = idx[suf[id]];
		g.nx[make_pair(idx[id], idx[suf[id]])] = rlas[suf[id]];
		g.nx[make_pair(llas[suf[id]], idx[suf[id]])] = idx[id];
		g.nx[make_pair(idx[suf[id]], idx[id])] = rlas[id];

		for (int i = 0; i < n; i++)
		{
			int nx = (i + 1) % n;
			g.nx[make_pair(nx, i)] = outeridx[i];
			g.nx[make_pair(i, outeridx[i])] = outeridx[nx];
			g.nx[make_pair(outeridx[i], outeridx[nx])] = nx;
			g.nx[make_pair(outeridx[nx], nx)] = i;
			g.nx[make_pair(outeridx[nx], outeridx[i])] = outeridx[(i + n - 1) % n];
		}

		return g;
	}
}

namespace Merge
{
	int n;
	vector<int> f, idx;
	Graph out;

	int getf(int u)
	{
		return f[u] == u ? u : f[u] = getf(f[u]);
	}

	void merge(int x, int y)
	{
		x = getf(x);
		y = getf(y);
		if (x == y)
			return;
		if (x < y)
			swap(x, y);
		f[x] = y;
	}

	Graph &work(Graph &g)
	{
		n = g.v.size();
		f.resize(n);
		idx.resize(n);
		for (int i = 0; i < n; i++)
			f[i] = i;
		for (auto e : g.e)
			if ((g.v[e.first] - g.v[e.second]).len() < radius * eps)
				merge(e.first, e.second);
		int cnt = 0;
		for (int i = 0; i < n; i++)
			if (f[i] == i)
			{
				out.v.emplace_back(g.v[i]);
				idx[i] = cnt++;
			}
		for (auto e : g.e)
			if (getf(e.first) != getf(e.second))
			{
				int u = getf(e.first), v = getf(e.second);
				if (u > v)
					swap(u, v);
				out.e.emplace_back(make_pair(idx[u], idx[v]));
				if (g.nx.count(make_pair(e.first, e.second)))
				{
					int x = e.first, y = e.second, z = g.nx[make_pair(x, y)];
					while (getf(z) == getf(e.second))
					{
						x = y;
						y = z;
						z = g.nx[make_pair(x, y)];
					}
					out.nx[make_pair(idx[getf(e.first)], idx[getf(e.second)])] = idx[getf(z)];
				}
				if (g.nx.count(make_pair(e.second, e.first)))
				{
					int x = e.second, y = e.first, z = g.nx[make_pair(x, y)];
					while (getf(z) == getf(e.first))
					{
						x = y;
						y = z;
						z = g.nx[make_pair(x, y)];
					}
					out.nx[make_pair(idx[getf(e.second)], idx[getf(e.first)])] = idx[getf(z)];
				}
			}
		sort(out.e.begin(), out.e.end());
		auto pos = unique(out.e.begin(), out.e.end());
		out.e.erase(pos, out.e.end());
		return out;
	}
}

namespace Regions
{
	int n;
	vector<int> p;
	Graph *in;

	typedef vector<int> Region;

	vector<Region> out;

	struct Edge
	{
		int from, to;
		Vec vec;

		Edge() {}

		Edge(int from, int to)
		{
			this->from = from;
			this->to = to;
			vec = (in->v[to] - in->v[from]).norm();
		}
	};

	vector<set<Edge>> eout;

	int quadrant(const Vec &vec)
	{
		if (vec.x > 0 && vec.y >= 0)
			return 1;
		if (vec.x <= 0 && vec.y > 0)
			return 2;
		if (vec.x < 0 && vec.y <= 0)
			return 3;
		if (vec.x >= 0 && vec.y < 0)
			return 4;
		return 0;
	}

	bool operator<(const Edge &x, const Edge &y)
	{
		if (quadrant(x.vec) != quadrant(y.vec))
			return quadrant(x.vec) > quadrant(y.vec);
		if (x.vec * y.vec != 0)
			return x.vec * y.vec < 0;
		return x.to < y.to;
	}

	bool cmp(int x, int y)
	{
		return in->v[x] < in->v[y];
	}

	vector<Region> &build(Graph &g)
	{
		n = g.v.size();
		in = &g;
		p.resize(n);
		eout.resize(n);
		for (int i = 0; i < n; i++)
			p[i] = i;
		for (auto e : g.e)
		{
			eout[e.first].insert(Edge(e.first, e.second));
			eout[e.second].insert(Edge(e.second, e.first));
		}
		sort(p.begin(), p.end(), cmp);
		for (int i = 0; i < n; i++)
		{
			int cur = p[i];
			while (eout[cur].size() > 0)
			{
				Region r;
				r.clear();
				auto e = eout[cur].begin();
				while (true)
				{
					int from = e->from;
					int to = e->to;
					r.emplace_back(from);
					Edge rev = Edge(to, from);
					eout[from].erase(e);
					if (to == cur)
						break;
					if (g.nx.count(make_pair(from, to)))
						e = eout[to].lower_bound(Edge(to, g.nx[make_pair(from, to)]));
					else
					{
						auto nx = eout[to].upper_bound(rev);
						if (nx == eout[to].end())
							nx = eout[to].begin();
						e = nx;
					}
				}
				long double area = 0;
				int len = r.size();
				for (int i = 0; i < len; i++)
					area += (g.v[r[i]] - g.v[r[0]]) * (g.v[r[(i + 1) % len]] - g.v[r[0]]);
				if (area < 0)
					continue;
				out.emplace_back(r);
			}
		}
		return out;
	}
}

namespace Scan
{
	int n, m;
	vector<Point> *vp, *qp;
	vector<int> p, rk;

	vector<long double> ans;

	bool cmp(int x, int y)
	{
		Point xp = x < n ? (*vp)[x] : (*qp)[x - n];
		Point yp = y < n ? (*vp)[y] : (*qp)[y - n];
		return xp < yp;
	}

	long double x, y;
	long double direps;

	struct Edge
	{
		int sid, tid;
		Vec s, t, dir;
		int bel;

		Edge() {}

		Edge(Point p)
		{
			this->s = p - Vec(1, 0);
			this->t = p + Vec(1, 0);
			this->dir = (t - s).norm(EXTEND);
		}

		Edge(int sid, int tid, int bel)
		{
			this->sid = sid;
			this->tid = tid;
			s = (*vp)[sid];
			t = (*vp)[tid];
			this->dir = (t - s).norm(EXTEND);
			this->bel = bel;
		}

		Point at(long double x) const
		{
			long double lambda = (x - s.x) / (t.x - s.x);
			if (isnan(lambda) || isinf(lambda))
				return Point(x, y);
			return s + lambda * (t - s);
		}
	};

	bool operator<(const Edge &a, const Edge &b)
	{
		long double ay = a.at(x).y, by = b.at(x).y;
		if (ay != by)
			return ay < by;
		if (a.dir.y != b.dir.y)
			return a.dir.y * direps < b.dir.y * direps;
		if (a.sid != b.sid)
			return a.sid < b.sid;
		return a.tid < b.tid;
	}

	vector<vector<Edge>> ein, eout;
	set<Edge> s;

	long double dist(Vec &p, Vec &s, Vec &t)
	{
		if (((p - s) ^ (t - s)) < 0)
			return (p - s).len();
		if (((p - t) ^ (s - t)) < 0)
			return (p - t).len();
		long double len = (p - s) ^ (t - s).norm();
		return (p - (s + (t - s).norm(len))).len();
	}

	vector<long double> &work(int c, vector<Point> &v, vector<Regions::Region> &r, vector<Point> &q)
	{
		vp = &v;
		qp = &q;
		n = v.size();
		m = q.size();
		p.resize(n + m);
		rk.resize(n);
		ein.resize(n);
		eout.resize(n);
		ans.resize(m);
		for (int i = 0; i < n + m; i++)
			p[i] = i;
		sort(p.begin(), p.end(), cmp);
		for (int i = 0; i < n + m; i++)
			if (p[i] < n)
				rk[p[i]] = i;
		for (auto region : r)
		{
			int len = region.size();
			int fir = n, sec = n;
			for (int i = 0; i < len; i++)
				if (region[i] < c)
				{
					if (region[i] < fir)
					{
						sec = fir;
						fir = region[i];
					}
					else if (region[i] < sec)
						sec = region[i];
				}
			int bel = fir;
			if (fir == 0 && sec > 1)
				bel = sec;

			for (int i = 0, idx; i < len - 1; i = idx)
			{
				idx = i + 1;
				int from = region[i], to = region[idx % len];
				while (idx < len && rk[from] > rk[to])
				{
					idx++;
					to = region[idx % len];
				}
				if (idx >= len)
					break;
				Edge e = Edge(from, to, bel);
				eout[from].emplace_back(e);
				ein[to].emplace_back(e);
			}
		}
		for (int i = 0; i < n + m; i++)
		{
			if (p[i] < n)
			{
				x = v[p[i]].x;
				y = v[p[i]].y;
				direps = -1;
				for (auto e : ein[p[i]])
					s.erase(e);
				direps = 1;
				for (auto e : eout[p[i]])
					s.insert(e);
			}
			else
			{
				x = q[p[i] - n].x;
				y = q[p[i] - n].y;
				direps = 1;
				auto e = s.upper_bound(Edge(q[p[i] - n]));
				e--;
				int bel = e->bel;
				ans[p[i] - n] = dist(q[p[i] - n], v[bel], v[(bel + 1) % c]);
			}
		}
		return ans;
	}
}

int n, q;
Polygon convex;
vector<Point> queries;
Graph g;
vector<Regions::Region> r;
vector<long double> ans;

int main()
{
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		convex.emplace_back(Point().read());
	scanf("%d", &q);
	for (int i = 0; i < q; i++)
		queries.emplace_back(Point().read());

	g = Diagram::build(convex);
	g = Merge::work(g);
	r = Regions::build(g);
	ans = Scan::work(n, g.v, r, queries);

	for (int i = 0; i < q; i++)
		printf("%.10Lf\n", ans[i]);

	return 0;
}