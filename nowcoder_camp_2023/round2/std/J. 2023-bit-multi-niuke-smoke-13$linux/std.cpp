#include <bits/stdc++.h>

using LL = long long;
using ld = long double;
using Pair = std::pair<int, int>;
#define inf 1'000'000'000'000'000ll
std::mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());

template <int kcz>
struct ModInt
{
#define T (*this)
    int x;

    ModInt() : x(0) {}

    ModInt(int y) : x(y >= 0 ? y : y + kcz) {}

    ModInt(LL y) : x(y >= 0 ? y % kcz : (kcz - (-y) % kcz) % kcz) {}

    inline int inc(const int &v)
    {
        return v >= kcz ? v - kcz : v;
    }

    inline int dec(const int &v)
    {
        return v < 0 ? v + kcz : v;
    }

    inline ModInt &operator+=(const ModInt &p)
    {
        x = inc(x + p.x);
        return T;
    }

    inline ModInt &operator-=(const ModInt &p)
    {
        x = dec(x - p.x);
        return T;
    }

    inline ModInt &operator*=(const ModInt &p)
    {
        x = (int)((LL)x * p.x % kcz);
        return T;
    }

    inline ModInt inverse() const
    {
        int a = x, b = kcz, u = 1, v = 0, t;
        while (b > 0)
            t = a / b, std::swap(a -= t * b, b), std::swap(u -= t * v, v);
        return u;
    }

    inline ModInt &operator/=(const ModInt &p)
    {
        T *= p.inverse();
        return T;
    }

    inline ModInt operator-() const
    {
        return -x;
    }

    inline friend ModInt operator+(const ModInt &lhs, const ModInt &rhs)
    {
        return ModInt(lhs) += rhs;
    }

    inline friend ModInt operator-(const ModInt &lhs, const ModInt &rhs)
    {
        return ModInt(lhs) -= rhs;
    }

    inline friend ModInt operator*(const ModInt &lhs, const ModInt &rhs)
    {
        return ModInt(lhs) *= rhs;
    }

    inline friend ModInt operator/(const ModInt &lhs, const ModInt &rhs)
    {
        return ModInt(lhs) /= rhs;
    }

    inline bool operator==(const ModInt &p) const
    {
        return x == p.x;
    }

    inline bool operator!=(const ModInt &p) const
    {
        return x != p.x;
    }

    inline ModInt qpow(LL n) const
    {
        ModInt ret(1), mul(x);
        while (n > 0)
        {
            if (n & 1)
                ret *= mul;
            mul *= mul, n >>= 1;
        }
        return ret;
    }

    inline friend std::ostream &operator<<(std::ostream &os, const ModInt &p)
    {
        return os << p.x;
    }

    inline friend std::istream &operator>>(std::istream &is, ModInt &a)
    {
        LL t;
        is >> t, a = ModInt<kcz>(t);
        return is;
    }

    static int get_mod()
    {
        return kcz;
    }

    inline bool operator<(const ModInt &A) const
    {
        return x < A.x;
    }

    inline bool operator>(const ModInt &A) const
    {
        return x > A.x;
    }

#undef T
};

const int kcz = 998244353;
using Z = ModInt<kcz>;

namespace NTT
{
    std::vector<int> rev;
    std::vector<Z> roots{0, 1};

    inline void dft(std::vector<Z> &a)
    {
        int n = (int)(a.size());
        if (rev.size() != n)
        {
            int k = __builtin_ctz(n) - 1;
            rev.resize(n);
            for (int i = 0; i < n; i++)
                rev[i] = rev[i >> 1] >> 1 | (i & 1) << k;
        }
        for (int i = 0; i < n; i++)
            if (rev[i] < i)
                std::swap(a[i], a[rev[i]]);
        if (roots.size() < n)
        {
            int k = __builtin_ctz(roots.size());
            roots.resize(n);
            while ((1 << k) < n)
            {
                Z e = Z(3).qpow((kcz - 1) >> (k + 1));
                for (int i = 1 << (k - 1); i < (1 << k); i++)
                    roots[i << 1] = roots[i], roots[i << 1 | 1] = roots[i] * e;
                k++;
            }
        }
        for (int k = 1; k < n; k <<= 1)
        {
            for (int i = 0; i < n; i += k << 1)
            {
                for (int j = 0; j < k; j++)
                {
                    Z u = a[i + j], v = a[i + j + k] * roots[k + j];
                    a[i + j] = u + v, a[i + j + k] = u - v;
                }
            }
        }
    }

    inline void idft(std::vector<Z> &a)
    {
        int n = (int)(a.size());
        reverse(a.begin() + 1, a.end()), dft(a);
        Z inv = Z(n).inverse();
        for (int i = 0; i < n; i++)
            a[i] = a[i] * inv;
    }
}
struct Poly : public std::vector<Z>
{
#define T (*this)
    using vector<Z>::vector;

    inline int deg() const
    {
        return (int)(size());
    }

    inline Z operator[](const int &idx) const
    {
        if (idx < 0 || idx >= deg())
            return Z(0);
        return at(idx);
    }

    inline Z &operator[](const int &idx)
    {
        return at(idx);
    }

    inline Poly &operator^=(const Poly &b)
    {
        if (b.deg() < deg())
            resize(b.deg());
        for (int i = 0, sz = deg(); i < sz; i++)
            T[i] *= b[i];
        return T;
    }

    inline Poly &operator<<=(const int &k)
    {
        return insert(begin(), k, Z(0)), T;
    }

    inline Poly operator<<(const int &r) const
    {
        return Poly(T) <<= r;
    }

    inline Poly operator>>(const int &r) const
    {
        return r >= deg() ? Poly() : Poly(begin() + r, end());
    }

    inline Poly &operator>>=(const int &r)
    {
        return T = T >> r;
    }

    inline Poly mod(const int &k) const
    {
        return k < deg() ? Poly(begin(), begin() + k) : T;
    }

    inline friend Poly operator*(const Z &a, Poly b)
    {
        for (auto &x : b)
            x *= a;
        return b;
    }

    inline friend Poly operator*(Poly b, const Z &a)
    {
        for (auto &x : b)
            x *= a;
        return b;
    }

    inline friend Poly operator*(Poly a, Poly b)
    {
        if (a.empty() || b.empty())
            return {};
        int sz = 1, tot = a.deg() + b.deg() - 1;
        while (sz < tot)
            sz <<= 1;
        a.resize(sz), b.resize(sz);
        NTT::dft(a), NTT::dft(b);
        for (int i = 0; i < sz; i++)
            a[i] *= b[i];
        NTT::idft(a), a.resize(tot);
        return a;
    }

    inline Poly &operator*=(const Poly &b)
    {
        return T = T * b;
    }

    inline friend Poly operator+(const Poly &a, const Poly &b)
    {
        int n = (int)std::max(a.size(), b.size());
        Poly c;
        c.resize(n);
        for (int i = 0, sz = (int)a.size(); i < sz; i++)
            c[i] = a[i];
        for (int i = 0, sz = (int)b.size(); i < sz; i++)
            c[i] += b[i];
        return c;
    }

    inline Poly &operator+=(const Poly &b)
    {
        return T = T + b;
    }

    inline friend Poly operator-(const Poly &a, const Poly &b)
    {
        int n = (int)std::max(a.size(), b.size());
        Poly c;
        c.resize(n);
        for (int i = 0, sz = (int)a.size(); i < sz; i++)
            c[i] = a[i];
        for (int i = 0, sz = (int)b.size(); i < sz; i++)
            c[i] -= b[i];
        return c;
    }

    inline Poly &operator-=(const Poly &b)
    {
        return T = T - b;
    }

    inline Poly derivation() const
    {
        if (T.empty())
            return {};
        int n = (int)(T.size());
        Poly c;
        c.resize(n - 1);
        for (int i = 0; i < n - 1; i++)
            c[i] = T[i + 1] * (i + 1);
        return c;
    }

    inline Poly integration() const
    {
        int n = (int)(T.size());
        Poly c;
        c.resize(n + 1);
        for (int i = 0; i < n; i++)
            c[i + 1] = T[i] * Z(i + 1).inverse();
        return c;
    }

    inline Poly inv(const int &m) const
    {
        Poly c{T[0].inverse()};
        int k = 1;
        while (k < m)
            k <<= 1, c = (c * (Poly{2} - T.mod(k) * c)).mod(k);
        return c.mod(m);
    }

    inline Poly log(const int &m) const
    {
        return (derivation() * inv(m)).integration().mod(m);
    }

    inline Poly exp(const int &m) const
    {
        Poly x{1};
        int k = 1;
        while (k < m)
            k <<= 1, x = (x * (Poly{1} - x.log(k) + mod(k))).mod(k);
        return x.mod(m);
    }

    inline Poly pow(const int &k, const int &m) const
    {
        int i = 0;
        while (i < T.size() && T[i] == Z(0))
            i++;
        if (i == T.size() || (LL)i * k >= m)
            return Poly(m);
        Z v = T[i];
        auto g = (T >> i) * (v.inverse());
        return ((g.log(m - i * k) * Z(k)).exp(m - i * k) << (i * k)) * v.qpow(k);
    }

    inline Poly sqrt(const int &m) const
    {
        Poly x{1};
        int k = 1;
        while (k < m)
            k <<= 1, x = (x + (mod(k) * x.inv(k)).mod(k)) * Z(2).inverse();
        return x.mod(m);
    }

    inline Poly rev() const
    {
        return Poly(rbegin(), rend());
    }

    inline Poly mulT(const Poly &b) const
    {
        return T * b.rev() >> (b.deg() - 1);
    }

    inline vector<Z> eval(vector<Z> x) const
    {
        if (T.empty())
            return vector<Z>(x.size(), Z(0));
        int n = std::max((int)(x.size()), (int)(T.size()));
        vector<Poly> q(4 * n);
        vector<Z> ans(x.size());
        x.resize(n);
        std::function<void(int, int, int)> build = [&](int rt, int l, int r)
        {
            if (l == r)
            {
                q[rt] = {Z(1), -x[l]};
                return;
            }
            int mid = (l + r) >> 1;
            build(rt << 1, l, mid), build(rt << 1 | 1, mid + 1, r);
            q[rt] = q[rt << 1] * q[rt << 1 | 1];
        };
        build(1, 0, n - 1);
        std::function<void(int, int, int, const Poly &)> work = [&](int rt, int l, int r, const Poly &num)
        {
            if (l == r)
            {
                if (l < (int)(ans.size()))
                    ans[l] = num[0];
                return;
            }
            int mid = (l + r) >> 1;
            work(rt << 1, l, mid, num.mulT(q[rt << 1 | 1]).mod(mid - l + 1));
            work(rt << 1 | 1, mid + 1, r, num.mulT(q[rt << 1]).mod(r - mid));
        };
        work(1, 0, n - 1, mulT(q[1].inv(n)));
        return ans;
    }

#undef T
};

struct P
{
    Poly L, R, S, DE, ans;

    inline friend P operator+(const P &lhs, const P &rhs)
    {
        return {rhs.L * lhs.DE + lhs.L * rhs.S, lhs.R * rhs.DE + rhs.R * lhs.S, lhs.S * rhs.S, lhs.DE * rhs.DE, lhs.ans * rhs.DE + rhs.ans * lhs.DE + lhs.L * rhs.R};
    }
};

inline void solve()
{
    int n, m;
    Z p;
    std::cin >> n >> m >> p;
    std::vector<Z> A(n + m - 1), B(n + m - 1), C(n), D(m);
    for (auto &x : A)
        std::cin >> x, x *= p;
    for (auto &x : B)
        std::cin >> x, x *= 1 - p;
    for (auto &x : C)
        std::cin >> x, x *= 1 - p;
    for (auto &x : D)
        std::cin >> x, x /= m;
    std::function<P(int, int)> solve = [&](int l, int r)
    {
        if (l == r)
        {
            Poly DE = Poly{1, -B[l]};
            Poly ans{};
            if (l < m)
                ans = Poly{D[l]};
            Poly L{};
            if (l < m)
                L = Poly{0, D[l] * A[l]};
            Poly R = Poly{1};
            Poly S = Poly{0, A[l]};
            return P{L, R, S, DE, ans};
        }
        int mid = (l + r) >> 1;
        auto L = solve(l, mid), R = solve(mid + 1, r);
        auto LR = L + R;
        return LR;
    };
    const auto &now = solve(0, n + m - 1);
    Poly Ans = (now.ans * now.DE.inv(n + 1)).mod(n + 1);
    std::vector<Poly> tr((n + 1) << 2 | 1);
    std::function<void(int, int, int)> pre = [&](int rt, int l, int r)
    {
        if (l == r)
        {
            tr[rt] = Poly{1, C[l - 1]};
            return;
        }
        int mid = (l + r) >> 1;
        pre(rt << 1, l, mid), pre(rt << 1 | 1, mid + 1, r);
        tr[rt] = tr[rt << 1] * tr[rt << 1 | 1];
    };
    pre(1, 1, n);
    Poly ans(n + 1);
    std::function<void(int, int, int, Poly)> Solve = [&](int rt, int l, int r, Poly P)
    {
        if (l == r)
        {
            ans[l] = P[0] * tr[rt][1] + P[1];
            return;
        }
        int mid = (l + r) >> 1;
        Solve(rt << 1, l, mid, P.mod(mid - l + 2));
        P *= tr[rt << 1];
        Solve(rt << 1 | 1, mid + 1, r, P.mod(r - l + 2) >> (mid - l + 1));
    };
    Solve(1, 1, n, Ans);
    for (int i = 1; i <= n; i++)
        std::cout << ans[i] << '\n';
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    int T = 1;
    while (T--)
        solve();
    return 0;
}
