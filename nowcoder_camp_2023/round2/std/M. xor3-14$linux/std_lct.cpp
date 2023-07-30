#include <bits/stdc++.h>
using namespace std;
using ll = long long;

using a2 = array<int, 2>;
using a2l = array<ll, 2>;
using a2a = const a2 &;
using a2la = const a2l &;

a2 operator+(a2a a, a2a b)
{
    return {a[0] + b[0], a[1] + b[1]};
}
a2 operator-(a2a a, a2a b)
{
    return {a[0] - b[0], a[1] - b[1]};
}
a2 operator^(a2a a, int b)
{
    return {a[b], a[b ^ 1]};
}
a2l operator+(a2la a, a2la b)
{
    return {a[0] + b[0], a[1] + b[1]};
}
ll dot(a2a a, a2a b)
{
    return 1ll * a[0] * b[0] + 1ll * a[1] * b[1];
}
a2 sum0(a2a a)
{
    return {a[0] + a[1], 0};
}
a2 sum1(a2a a)
{
    return {0, a[0] + a[1]};
}
ll calc0(a2a a)
{
    return (a[0] * (a[0] - 1ll) + a[1] * (a[1] - 1ll)) / 2;
}
ll calc1(a2a a)
{
    return 1ll * a[0] * a[1];
}

struct LCT
{
    struct T
    {
        int fa, val, covertag;
        a2 s, pcv;
        a2l ansp;
        a2 cv, crv, clk;
        a2l ansv;
        ll ans;
        T()
        {
            memset(this, 0, sizeof(*this));
            covertag = -1;
        }
        void init()
        {
            cv = pcv;
            crv = pcv ^ val;
            clk.fill(0);
            clk[val]++;
            ansv[0] = ansp[0] + calc0(cv) + cv[0];
            ansv[1] = ansp[1] + calc1(cv) + cv[0];
            ans = ansv[val];
        }
        void ml(const T &l)
        {
            ans += l.ans + dot(l.crv + sum0(l.clk), cv + clk);
            ansv[0] += dot(l.cv + sum0(l.clk), cv + sum0(clk)) + l.ansv[0];
            ansv[1] += dot((l.cv ^ 1) + sum0(l.clk), cv + sum1(clk)) + l.ansv[1];
            cv = cv + l.cv;
            crv = crv + l.crv;
            clk = clk + l.clk;
        }
        void mr(const T &r)
        {
            ans += r.ans + dot(crv + sum0(clk), r.cv + r.clk);
            ansv[0] += dot(cv + sum0(clk), r.cv + sum0(r.clk)) + r.ansv[0];
            ansv[1] += dot((cv ^ 1) + sum0(clk), r.cv + sum1(r.clk)) + r.ansv[1];
            cv = cv + r.cv;
            crv = crv + r.crv;
            clk = clk + r.clk;
        }
        void cover(int tag)
        {
            covertag = tag;
            val = tag;
            ans = ansv[tag];
            clk[tag] += clk[tag ^ 1];
            clk[tag ^ 1] = 0;
            crv = (tag == 0) ? cv : (cv ^ 1);
        }
        void cleartag()
        {
            covertag = -1;
        }
    };
    LCT(int n) : t(n + 1)
    {
        for (int i = 1; i <= n; i++)
        {
            cin >> t[i].val;
        }
        for (int i = 2; i <= n; i++)
        {
            cin >> t[i].fa;
        }
        for (int i = n; i >= 1; i--)
        {
            t[i].init();
            if (t[i].fa)
            {
                remover(t[i].fa, i);
            }
        }
    }
    vector<T> t;
    bool gets(int v)
    {
        return t[t[v].fa].s[1] == v;
    }
    bool isr(int v)
    {
        return t[t[v].fa].s[gets(v)] != v;
    }
    void pu(int v)
    {
        t[v].init();
        if (t[v].s[0])
        {
            t[v].ml(t[t[v].s[0]]);
        }
        if (t[v].s[1])
        {
            t[v].mr(t[t[v].s[1]]);
        }
    }
    void pd(int v)
    {
        if (t[v].covertag != -1)
        {
            if (t[v].s[0])
            {
                t[t[v].s[0]].cover(t[v].covertag);
            }
            if (t[v].s[1])
            {
                t[t[v].s[1]].cover(t[v].covertag);
            }
            t[v].cleartag();
        }
    }
    void rotate(int v)
    {
        int u = t[v].fa, w = t[u].fa;
        int sv = gets(v), su = gets(u);
        t[u].s[sv] = t[v].s[sv ^ 1];
        t[v].s[sv ^ 1] = u;
        if (!isr(u))
        {
            t[w].s[su] = v;
        }
        t[t[u].s[sv]].fa = u, pu(u);
        t[u].fa = v, t[v].fa = w;
    }
    void pushdown(int v)
    {
        if (!isr(v))
        {
            pushdown(t[v].fa);
        }
        pd(v);
    }
    void splay(int v)
    {
        for (pushdown(v); !isr(v) && !isr(t[v].fa); rotate(v))
        {
            if (gets(v) != gets(t[v].fa))
            {
                rotate(v);
            }
            else
            {
                rotate(t[v].fa);
            }
        }
        if (!isr(v))
        {
            rotate(v);
        }
        pu(v);
    }
    void remover(int v, int u)
    {
        if (u)
        {
            t[v].s[1] = 0;
            a2 cnt = t[u].cv + t[u].clk;
            t[v].pcv = t[v].pcv + cnt;
            t[v].ansp[0] += t[u].ans - calc0(cnt);
            t[v].ansp[1] += t[u].ans - calc1(cnt);
        }
    }
    void insertr(int v, int u)
    {
        remover(v, t[v].s[1]);
        if (u)
        {
            a2 cnt = t[u].cv + t[u].clk;
            t[v].s[1] = u;
            t[v].pcv = t[v].pcv - cnt;
            t[v].ansp[0] -= t[u].ans - calc0(cnt);
            t[v].ansp[1] -= t[u].ans - calc1(cnt);
        }
        pu(v);
    }
    int access(int v)
    {
        int w = 0;
        while (v)
        {
            splay(v);
            insertr(v, w);
            w = v, v = t[v].fa;
        }
        return w;
    }
    void cover(int u, int v, int tag)
    {
        access(u);
        int w = access(v);
        pd(w);
        if (t[w].s[1])
        {
            t[t[w].s[1]].cover(tag);
        }
        t[w].val = tag;
        pu(w);
        splay(v);
        w = access(u);
        pd(w);
        if (t[w].s[1])
        {
            t[t[w].s[1]].cover(tag);
            pu(w);
        }
        splay(u);
    }
    ll query(int v)
    {
        access(v);
        splay(v);
        t[v].init();
        ll res = t[v].ans;
        pu(v);
        return res;
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    int n, q;
    cin >> n >> q;
    LCT lct(n);
    for (int i = 1; i <= q; i++)
    {
        int op, x, y, z;
        cin >> op >> x;
        if (op == 1)
        {
            cin >> y >> z;
            lct.cover(x, y, z);
        }
        else
        {
            printf("%lld\n", lct.query(x));
        }
    }
    return 0;
}
