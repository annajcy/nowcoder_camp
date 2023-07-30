#ifndef WORKSPACE_TEMPLATE_H
#define WORKSPACE_TEMPLATE_H

#include <bits/stdc++.h>
#define mp std::make_pair
#define scanf dont_use_scanf
#define printf dont_use_printf
#define puts dont_use_puts
#define endl dont_use_endl

using ll = long long;
using pii = std::pair<int, int>;
using piii = std::tuple<int, int, int>;
using piiii = std::tuple<int, int, int, int>;
using pll = std::pair<ll, ll>;
using plll = std::tuple<ll, ll, ll>;
using pllll = std::tuple<ll, ll, ll, ll>;
// using Mint = Mod<UNDEFINED>;

#include <bits/stdc++.h>

class DominatorTree
{
public:
    std::vector<std::vector<int>> e, _e, tmp;
    std::vector<int> dfn, inv;
    int dfncnt;
    std::vector<int> sdom, idom;
    std::vector<int> fa, father, value;

    explicit DominatorTree(int n) : dfncnt(0)
    {
        int sz = n + 10;
        e.resize(sz);
        _e.resize(sz);
        tmp.resize(sz);
        dfn.resize(sz);
        inv.resize(sz);
        sdom.resize(sz);
        idom.resize(sz);
        fa.resize(sz);
        father.resize(sz);
        value.resize(sz);
    }

    void add_edge(int u, int v)
    {
        e[u].emplace_back(v);
        _e[v].emplace_back(u);
    }

    int min(int u, int v)
    {
        return dfn[u] < dfn[v] ? u : v;
    }

    int find(int u)
    {
        if (fa[u] == u)
            return u;
        int f = fa[u];
        fa[u] = find(fa[u]);
        if (dfn[sdom[value[f]]] < dfn[sdom[value[u]]])
            value[u] = value[f];
        return fa[u];
    }

    void dfs(int u)
    {
        dfn[u] = ++dfncnt;
        inv[dfncnt] = u;
        for (auto v : e[u])
        {
            if (dfn[v])
            {
                continue;
            }
            father[v] = u;
            dfs(v);
        }
    }

    void solve(int rt)
    {
        dfs(rt);
        for (int i = 1; i <= dfncnt; ++i)
        {
            fa[inv[i]] = value[inv[i]] = sdom[inv[i]] = inv[i];
        }
        for (int i = dfncnt; i >= 2; --i)
        {
            int u = inv[i];
            for (auto v : _e[u])
            {
                if (!dfn[v])
                    continue;
                if (dfn[v] < i)
                {
                    sdom[u] = min(sdom[u], v);
                }
                else
                {
                    find(v);
                    sdom[u] = min(sdom[u], sdom[value[v]]);
                }
            }
            fa[u] = father[u];
            tmp[sdom[u]].emplace_back(u);
            int pa = fa[u];
            for (auto v : tmp[pa])
            {
                find(v);
                idom[v] = value[v];
            }
            tmp[pa].clear();
        }
        for (int i = 2; i <= dfncnt; ++i)
        {
            int u = inv[i];
            idom[u] = sdom[u] == sdom[idom[u]] ? sdom[u] : idom[idom[u]];
        }
    }
};

class DfsOrder
{
public:
    std::vector<std::vector<int>> e;
    std::vector<int> dfn, right, dep;
    int dfn_cnt;
    int n, root;

    explicit DfsOrder(int sz, int root) : n(sz), dfn_cnt(0), root(root)
    {
        sz += 10;
        e.resize(sz);
        dfn.resize(sz);
        right.resize(sz);
        dep.resize(sz);
    }

    void add_edge(int u, int v)
    {
        e[u].emplace_back(v);
        e[v].emplace_back(u);
    }

    void dfs(int u, int fa)
    {
        dfn[u] = ++dfn_cnt;
        for (auto v : e[u])
        {
            if (v == fa)
            {
                continue;
            }
            dep[v] = dep[u] + 1;
            dfs(v, u);
        }
        right[u] = dfn_cnt;
    }

    void solve()
    {
        dfs(root, 0);
    }

    bool is_son(int u, int v)
    {
        return dfn[u] <= dfn[v] && right[v] <= right[u];
    }
};

class Solver
{
public:
    Solver() {}

    void solve()
    {
        int n, m;
        std::cin >> n >> m;
        std::vector<pii> edges;
        DominatorTree dominatorTree(n);
        for (int i = 0; i < m; ++i)
        {
            int u, v;
            std::cin >> u >> v;
            if (u == v)
            {
                continue;
            }
            edges.emplace_back(u, v);
            dominatorTree.add_edge(u, v);
        }
        dominatorTree.solve(1);
        std::vector<int> dis(n + 1, -1);
        std::queue<int> queue;
        queue.emplace(1);
        dis[1] = 0;
        while (!queue.empty())
        {
            int u = queue.front();
            queue.pop();
            for (auto v : dominatorTree.e[u])
            {
                if (dis[v] == -1)
                {
                    dis[v] = dis[u] + 1;
                    queue.emplace(v);
                }
            }
        }
        DfsOrder dfsOrder(n, 1);
        for (int i = 2; i <= n; ++i)
        {
            dfsOrder.add_edge(i, dominatorTree.idom[i]);
        }
        dfsOrder.solve();
        for (auto [u, v] : edges)
        {
            if (dis[u] + 1 == dis[v])
            {
                // should do nothing
            }
            else if (dis[u] == dis[v])
            {
                std::cout << "No\n";
                return;
            }
            else
            {
                if (!dfsOrder.is_son(v, u))
                {
                    std::cout << "No\n";
                    return;
                }
            }
        }
        std::cout << "Yes\n";
    }
};

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    int test = 1;
    std::cin >> test;
    // floating point number output template
    std::cout << std::fixed << std::setprecision(18);
    while (test--)
    {
        Solver solver;
        solver.solve();
    }
    return 0;
}

#endif // WORKSPACE_TEMPLATE_H
