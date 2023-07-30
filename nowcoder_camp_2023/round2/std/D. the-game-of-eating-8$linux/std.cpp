#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
void solve()
{
    int n, m, k;
    cin >> n >> m >> k;
    vector a(n, vector<int>(m));
    for (auto &b : a)
        for (auto &c : b)
            cin >> c;
    vector<bool> vis(m);
    auto findmax = [&](int i)
    {
        int cur = -1, res = 0;
        for (int j = 0; j < m; j++)
        {
            if (vis[j])
                continue;
            if (cur < a[i][j])
                cur = a[i][j], res = j;
        }
        return res;
    };
    vector<int> ans;
    for (int i = 0, p = (k - 1) % n; i < k; i++, p--)
    {
        if (p < 0)
            p = n - 1;
        int mx = findmax(p);
        vis[mx] = true;
        ans.push_back(mx + 1);
    }
    sort(begin(ans), end(ans));
    for (auto v : ans)
        printf("%d ", v);
    puts("");
    return;
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
/*
证明：by OMG_link
假设所有人都知道，当剩余菜集合为A时，最后k个人一定会保证S[A,k]集合内的所有菜都被选。进行归纳：
1. k=1情况显然；
2. k>1时：
    2.1 假设A中除S[A,k-1]以外第k个人最喜欢的菜存在，记为x：
        2.1.1 假设第k个人选x，得到集合S[A,k]
        2.1.2 假设第k个人选S[A,k-1]和x以外的菜，根据归纳前提，剩下k-1个菜一定是S[A,k-1]，因此第k个人一定亏
        2.1.3 假设第k个人选S[A,k-1]内的菜，则根据归纳前提，剩余k-1人中恰有一人选择S[A,k]以外的菜，若：
            2.1.3.1 这个人选的是菜x，则得到S[A,k]
            2.1.3.2 这个人选的不是菜x，则第k个人一定亏
    2.2 这时没有2.2了，菜x一定存在

1
3 4 3
1 2 3 4
3 1 2 4
1 3 2 4
*/
