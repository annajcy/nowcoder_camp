#include <bits/stdc++.h>
using namespace std;
using d80 = long double;
const d80 eps = 1e-9;

d80 zd(d80 val)
{
    return abs(val) < eps ? 0 : val;
}
bool leq(d80 a, d80 b)
{
    return zd(a - b) <= 0;
}
bool geq(d80 a, d80 b)
{
    return zd(a - b) >= 0;
}

struct P
{
    d80 x, y;
    friend istream &operator>>(istream &in, P &p)
    {
        int a, b;
        in >> a >> b;
        p.x = a, p.y = b;
        return in;
    }
    friend ostream &operator<<(ostream &out, const P &p)
    {
        out << zd(p.x) << ' ' << zd(p.y);
        return out;
    }
    void swap() { std::swap(x, y); }
    friend d80 len2(const P &a, const P &b)
    {
        return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
    }
    friend d80 len(const P &a, const P &b) { return sqrtl(len2(a, b)); }
    friend d80 lens(const P &a, const P &b)
    {
        return sqrtl(len2(a, b)) * (b.x >= a.x ? 1 : -1);
    }
    P go(const pair<P, P> &vec, d80 l)
    {
        auto &[a, b] = vec;
        d80 dx = b.x - a.x;
        d80 dy = b.y - a.y;
        d80 k = l / len(a, b);
        return {x + k * dx, y + k * dy};
    }
};

struct Line
{
    d80 a, b, c;
    Line(const P &p, const P &q)
    {
        a = p.y - q.y;
        b = q.x - p.x;
        move(p);
    }
    void move(const P &p) { c = -(a * p.x + b * p.y); }
    P cross(const Line &y) const
    {
        P res;
        res.x = (y.c * b - c * y.b) / (y.b * a - b * y.a);
        res.y = (c * y.a - y.c * a) / (y.b * a - b * y.a);
        return res;
    }
    Line clp(const P &p)
    {
        Line res = *this;
        swap(res.a, res.b);
        res.a = -res.a;
        res.move(p);
        return res;
    }
};

using t4 = tuple<P, P, P, P>;

pair<bool, t4> work(P pa, P pb, P pc, P pd)
{
    pair<bool, t4> res;
    auto &[ra, rb, rc, rd] = res.second;
    bool sac = false, sxy = false;
    if (pa.x == pc.x)
    {
        pa.swap(), pb.swap(), pc.swap(), pd.swap(), sxy = true;
    }

    if (pa.x < pc.x)
    {
        swap(pa, pc), sac = true;
    }
    Line lmid(pa, pc), lb = lmid, ld = lmid;
    lb.move(pb), ld.move(pd);
    Line lc = lmid.clp(pc);
    P cb = lc.cross(lb), cd = lc.cross(ld);
    d80 l2 = len2(pa, pc);
    d80 h2 = len2(cb, cd);
    if (zd(l2 - h2) < 0)
    {
        res.first = false;
        return res;
    }
    d80 dx = sqrtl(zd(l2 - h2)), l = sqrtl(l2);
    d80 xb = lens(cb, pb), xd = lens(cd, pd);
    d80 k = len(pc, cb) / len(pc, cd);
    d80 dd = dx / (k + 1), db = dd * k;
    if (geq(xb, db) && leq(xb, db + l) && geq(xd, -dd) && leq(xd, l - dd))
    {
        res.first = true;
        rd = cd.go({pc, pa}, -dd);
        rc = cb.go({pc, pa}, db);
        rb = rc.go({pc, pa}, l);
        ra = rd.go({pc, pa}, l);
    }
    else if (geq(xb, -db) && leq(xb, l - db) && geq(xd, dd) &&
             leq(xd, l + dd))
    {
        res.first = true;
        rd = cd.go({pc, pa}, dd);
        rc = cb.go({pc, pa}, -db);
        rb = rc.go({pc, pa}, l);
        ra = rd.go({pc, pa}, l);
    }
    if (sxy)
    {
        ra.swap(), rb.swap(), rc.swap(), rd.swap();
    }
    if (sac)
    {
        swap(ra, rd), swap(rb, rc);
    }
    return res;
}

void solve(const P &pa, const P &pb, const P &pc, const P &pd)
{
    auto res = work(pa, pb, pc, pd);
    if (res.first)
    {
        auto &[ra, rb, rc, rd] = res.second;
        cout << "Link doesn't cut tree!\n";
        cout << ra << ' ' << rb << ' ' << rc << ' ' << rd << "\n";
        return;
    }
    res = work(pb, pc, pd, pa);
    if (res.first)
    {
        auto &[rb, rc, rd, ra] = res.second;
        cout << "Link doesn't cut tree!\n";
        cout << ra << ' ' << rb << ' ' << rc << ' ' << rd << "\n";
        return;
    }
    cout << "Link cut tree!\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    int T;
    cout << fixed << setprecision(10);
    cin >> T;
    for (int t = 1; t <= T; t++)
    {
        P pa, pb, pc, pd;
        cin >> pa >> pb >> pc >> pd;
        /*if (T == 4480) {
            if (t == 29) {
                cout << pa << ' ' << pb << ' ' << pc << ' ' << pd << endl;
            } else {
                continue;
            }
        }*/
        solve(pa, pb, pc, pd);
    }
    return 0;
}
