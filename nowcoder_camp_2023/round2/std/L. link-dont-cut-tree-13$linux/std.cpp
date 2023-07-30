#pragma GCC target("avx2,sse,avx")

#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <utility>
using namespace std;
using ld = long double;
const ld eps = 1e-5;
struct V
{
    ld x, y;
    V(ld _x, ld _y) : x(_x), y(_y) {}
    V() : x(0), y(0) {}
    V operator-(const V &a) const
    {
        return V(x - a.x, y - a.y);
    };
    V operator+(const V &a) const
    {
        return V(x + a.x, y + a.y);
    };
    V operator*(const ld s) const
    {
        return V(x * s, y * s);
    }
};
struct Seg
{
    V s, t;
    Seg(V a, V b) : s(a), t(b) {}
};
ld dis(const V &a) { return sqrtl(a.x * a.x + a.y * a.y); }
ld dis(V a, V b) { return dis(a - b); }
V unitV(const V &v)
{
    ld f = dis(v);
    return V(v.x / f, v.y / f);
}
ld dot(const V &a, const V &b)
{
    return a.x * b.x + a.y * b.y;
}
ld cross(const V &a, const V &b)
{
    return a.x * b.y - a.y * b.x;
}
V cross(const Seg &A, const Seg &B)
{
    const auto &[a, b] = A;
    const auto &[c, d] = B;
    V n1(b.y - a.y, a.x - b.x);
    V n2(d.y - c.y, c.x - d.x);
    ld dist_c_n2 = c.x * n2.x + c.y * n2.y;
    ld dist_a_n2 = a.x * n2.x + a.y * n2.y;
    ld denominator = n1.x * n2.y - n1.y * n2.x;
    ld fraction = (dist_a_n2 - dist_c_n2) / denominator;
    return V(a.x + fraction * n1.y, a.y - fraction * n1.x);
}
ld S(V a, V b, V c)
{
    return abs(cross(b - a, c - a)) / 2;
}
int sgn(ld x)
{
    if (abs(x) < eps)
        return 0;
    if (x > 0)
        return 1;
    return -1;
}
bool point_on_segment(V p, Seg seg)
{
    if (sgn(cross(seg.s - p, p - seg.t)))
        return false;
    if (dot(seg.s - p, p - seg.t) + eps < 0)
        return false;
    return true;
};
array<array<V, 4>, 2> solve(const array<V, 4> &input)
{
    auto &[a, b, c, d] = input;
    V vac = unitV(c - a);
    ld len = dis(c - a);
    V nac = unitV({vac.y, -vac.x});
    ld pb = dot(b, nac), pd = dot(d, nac);
    ld p = abs(pb - pd);
    ld tmp = len * len - p * p;
    if (abs(tmp) < 1e-10)
        tmp = 0;
    ld q = sqrtl(tmp);
    V v1 = nac * p + vac * q;
    V v2 = nac * p - vac * q;
    V a1 = cross({a, a + v1}, {d, d + vac});
    V b1 = cross({a, a + v1}, {b, b + vac});
    V c1 = cross({c, c + v1}, {b, b + vac});
    V d1 = cross({c, c + v1}, {d, d + vac});
    V a2 = cross({a, a + v2}, {d, d + vac});
    V b2 = cross({a, a + v2}, {b, b + vac});
    V c2 = cross({c, c + v2}, {b, b + vac});
    V d2 = cross({c, c + v2}, {d, d + vac});
    return {
        (array<V, 4>){a1, b1, c1, d1},
        (array<V, 4>){a2, b2, c2, d2}};
}
bool check(const array<V, 4> &input, const array<V, 4> &res)
{
    auto &[A, B, C, D] = input;
    auto &[a, b, c, d] = res;
    ld s1 = S(A, B, D) + S(B, C, D);
    ld s2 = S(a, b, d) + S(b, c, d);
    // cout<<s1<<' '<<s2<<endl;
    if (abs(s2 - 2 * s1) > eps)
        return false;
    if (!point_on_segment(A, {a, b}))
        return false;
    if (!point_on_segment(B, {b, c}))
        return false;
    if (!point_on_segment(C, {c, d}))
        return false;
    if (!point_on_segment(D, {d, a}))
        return false;
    ld lab = dis(a, b), lbc = dis(b, c), lcd = dis(c, d), lda = dis(d, a);
    if (abs(lab - lbc) > eps)
        return false;
    if (abs(lab - lcd) > eps)
        return false;
    if (abs(lab - lda) > eps)
        return false;
    return true;
};
void print(const array<V, 4> &input)
{
    puts("Link doesn't cut tree!");
    for (auto [x, y] : input)
        printf("%.10Lf %.10Lf ", x, y);
    puts("");
}
void solve()
{
    array<V, 4> input;
    for (auto &[x, y] : input)
        cin >> x >> y;
    auto res = solve(input);
    const auto &[A, B, C, D] = input;
    for (int i = 0; i < 2; i++)
    {
        if (check({A, B, C, D}, res[i]))
        {
            print(res[i]);
            return;
        }
    }
    res = solve({B, C, D, A});
    for (int i = 0; i < 2; i++)
    {
        if (check({B, C, D, A}, res[i]))
        {
            auto [b, c, d, a] = res[i];
            print({a, b, c, d});
            return;
        }
    }
    puts("Link cut tree!");
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int t = 1;
    cin >> t;
    while (t--)
        solve();
    return 0;
}
