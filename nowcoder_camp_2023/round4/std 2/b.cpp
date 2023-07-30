#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
const int M = 998244353;
const int maxn = 1e5 + 3;
namespace fft
{
    struct num
    {
        double x, y;
        num() { x = y = 0; }
        num(double x, double y) : x(x), y(y) {}
    };
    inline num operator+(num a, num b) { return num(a.x + b.x, a.y + b.y); }
    inline num operator-(num a, num b) { return num(a.x - b.x, a.y - b.y); }
    inline num operator*(num a, num b) { return num(a.x * b.x - a.y * b.y, a.x * b.y + a.y * b.x); }
    inline num conj(num a) { return num(a.x, -a.y); }
    int base = 1;
    vector<num> roots = {{0, 0}, {1, 0}};
    vector<int> rev = {0, 1};
    const double PI = acosl(-1.0);
    void ensure_base(int nbase)
    {
        if (nbase <= base)
            return;
        rev.resize(1 << nbase);
        for (int i = 0; i < (1 << nbase); i++)
            rev[i] = (rev[i >> 1] >> 1) + ((i & 1) << (nbase - 1));
        roots.resize(1 << nbase);
        while (base < nbase)
        {
            double angle = 2 * PI / (1 << (base + 1));
            for (int i = 1 << (base - 1); i < (1 << base); i++)
            {
                roots[i << 1] = roots[i];
                double angle_i = angle * (2 * i + 1 - (1 << base));
                roots[(i << 1) + 1] = num(cos(angle_i), sin(angle_i));
            }
            base++;
        }
    }
    void fft(vector<num> &a, int n = -1)
    {
        if (n == -1)
            n = a.size();
        assert((n & (n - 1)) == 0);
        int zeros = __builtin_ctz(n);
        ensure_base(zeros);
        int shift = base - zeros;
        for (int i = 0; i < n; i++)
            if (i < (rev[i] >> shift))
                swap(a[i], a[rev[i] >> shift]);
        for (int k = 1; k < n; k <<= 1)
        {
            for (int i = 0; i < n; i += 2 * k)
            {
                for (int j = 0; j < k; j++)
                {
                    num z = a[i + j + k] * roots[j + k];
                    a[i + j + k] = a[i + j] - z;
                    a[i + j] = a[i + j] + z;
                }
            }
        }
    }
    vector<num> fa, fb;
    vector<ll> multiply(vector<int> &a, vector<int> &b)
    {
        int need = a.size() + b.size() - 1;
        int nbase = 0;
        while ((1 << nbase) < need)
            nbase++;
        ensure_base(nbase);
        int sz = 1 << nbase;
        if (sz > (int)fa.size())
            fa.resize(sz);
        for (int i = 0; i < sz; i++)
        {
            int x = (i < (int)a.size() ? a[i] : 0);
            int y = (i < (int)b.size() ? b[i] : 0);
            fa[i] = num(x, y);
        }
        fft(fa, sz);
        num r(0, -0.25 / sz);
        for (int i = 0; i <= (sz >> 1); i++)
        {
            int j = (sz - i) & (sz - 1);
            num z = (fa[j] * fa[j] - conj(fa[i] * fa[i])) * r;
            if (i != j)
                fa[j] = (fa[i] * fa[i] - conj(fa[j] * fa[j])) * r;
            fa[i] = z;
        }
        fft(fa, sz);
        vector<ll> res(need);
        for (int i = 0; i < need; i++)
            res[i] = fa[i].x + 0.5;
        return res;
    }
    vector<int> multiply_mod(vector<int> &a, vector<int> &b, int m, int eq = 0)
    {
        int need = a.size() + b.size() - 1;
        int nbase = 0;
        while ((1 << nbase) < need)
            nbase++;
        ensure_base(nbase);
        int sz = 1 << nbase;
        if (sz > (int)fa.size())
            fa.resize(sz);
        for (int i = 0; i < (int)a.size(); i++)
        {
            int x = (a[i] % m + m) % m;
            fa[i] = num(x & ((1 << 15) - 1), x >> 15);
        }
        fill(fa.begin() + a.size(), fa.begin() + sz, num{0, 0});
        fft(fa, sz);
        if (sz > (int)fb.size())
            fb.resize(sz);
        if (eq)
            copy(fa.begin(), fa.begin() + sz, fb.begin());
        else
        {
            for (int i = 0; i < (int)b.size(); i++)
            {
                int x = (b[i] % m + m) % m;
                fb[i] = num(x & ((1 << 15) - 1), x >> 15);
            }
            fill(fb.begin() + b.size(), fb.begin() + sz, num{0, 0});
            fft(fb, sz);
        }
        double ratio = 0.25 / sz;
        num r2(0, -1), r3(ratio, 0), r4(0, -ratio), r5(0, 1);
        for (int i = 0; i <= (sz >> 1); i++)
        {
            int j = (sz - i) & (sz - 1);
            num a1 = (fa[i] + conj(fa[j]));
            num a2 = (fa[i] - conj(fa[j])) * r2;
            num b1 = (fb[i] + conj(fb[j])) * r3;
            num b2 = (fb[i] - conj(fb[j])) * r4;
            if (i != j)
            {
                num c1 = (fa[j] + conj(fa[i]));
                num c2 = (fa[j] - conj(fa[i])) * r2;
                num d1 = (fb[j] + conj(fb[i])) * r3;
                num d2 = (fb[j] - conj(fb[i])) * r4;
                fa[i] = c1 * d1 + c2 * d2 * r5;
                fb[i] = c1 * d2 + c2 * d1;
            }
            fa[j] = a1 * b1 + a2 * b2 * r5;
            fb[j] = a1 * b2 + a2 * b1;
        }
        fft(fa, sz);
        fft(fb, sz);
        vector<int> res(need);
        for (int i = 0; i < need; i++)
        {
            ll aa = fa[i].x + 0.5;
            ll bb = fb[i].x + 0.5;
            ll cc = fa[i].y + 0.5;
            res[i] = (aa + ((bb % m) << 15) + ((cc % m) << 30)) % m;
        }
        return res;
    }
    vector<int> square_mod(vector<int> &a, int m)
    {
        return multiply_mod(a, a, m, 1);
    }
};
int n, m, k, p2[maxn];
int f[maxn];
char s[maxn];
void getfail(char *s)
{
    int m = strlen(s + 1);
    f[0] = f[1] = 0;
    for (int i = 2; i <= m; i++)
    {
        int j = f[i - 1];
        while (j > 0 && s[j + 1] != s[i])
            j = f[j];
        if (s[j + 1] == s[i])
            f[i] = j + 1;
        else
            f[i] = 0;
    }
}
void add(int &x, int y)
{
    x += y;
    if (x >= M)
        x -= M;
}
void dec(int &x, int y)
{
    x -= y;
    if (x < 0)
        x += M;
}
int g[maxn], h[maxn], r[maxn], ans, sum[maxn];
int inv2 = (M + 1) / 2;
void solve(int L, int R)
{
    if (L == R)
        return;
    int mid = (L + R) >> 1;
    solve(L, mid);
    if (L > 1)
    {
        int len = R - L;
        vi A(len, 0), B(len, 0);
        for (int i = 0; i < len; i++)
            B[i] = g[i + 1];
        for (int i = 0; i <= mid - L; i++)
            A[i] = h[i + L];
        vi D = fft::multiply_mod(A, B, M);
        // vi E=fft::multiply_mod(A,C,M);
        for (int i = mid + 1; i <= R; i++)
            dec(h[i], D[i - L - 1]); // dec(r[i],E[i-L-1]);

        for (int i = 0; i < len; i++)
            A[i] = B[i] = 0;
        for (int i = 0; i < len; i++)
            A[i] = h[i + 1];
        for (int i = 0; i <= mid - L; i++)
            B[i] = g[i + L];
        D = fft::multiply_mod(A, B, M);
        // E=fft::multiply_mod(A,C,M);
        for (int i = mid + 1; i <= R; i++)
            dec(h[i], D[i - L - 1]); // dec(r[i],E[i-L-1]);
    }
    else
    {
        int len = mid - L + 1;
        vi A(len, 0), B(len, 0);
        for (int i = 0; i < len; i++)
            A[i] = h[i + L], B[i] = g[i + 1];
        vi D = fft::multiply_mod(A, B, M);
        // vi E=fft::multiply_mod(A,C,M);
        for (int i = mid + 1; i <= R; i++)
            dec(h[i], D[i - L - 1]); // dec(r[i],E[i-L-1]);
    }
    solve(mid + 1, R);
}
int main()
{
    p2[0] = 1;
    for (int i = 1; i < maxn; i++)
        p2[i] = p2[i - 1] * 2 % M;
    cin >> n >> k >> s + 1;
    m = strlen(s + 1);
    getfail(s);
    for (int i = m; i <= n - m; i++)
        g[i] = p2[i - m];
    for (int i = f[m]; i; i = f[i])
        if (m - i <= n - m)
            g[m - i] = 1;

    for (int i = 0; i <= n - m; i++)
        h[i] = g[i], r[i] = p2[i];
    if (n <= m)
    {
        if (k == 0)
            cout << p2[n] - (n == m) << endl;
        else if (k == 1)
            cout << (n == m) << endl;
        else
            cout << 0 << endl;
        return 0;
    }
    solve(1, n - m);

    int cof = 1;
    for (int i = 1; i <= n - m; i++)
    {
        cof = 1ll * cof * inv2 % M;
        sum[i] = (sum[i - 1] + 1ll * cof * h[i]) % M;
        dec(r[i], 1ll * p2[i] * sum[i] % M);
    }

    /*
    for (int i=1;i<=n-m;i++){
        h[i]=g[i];
        for (int j=1;j<i;j++) dec(h[i],1ll*h[j]*g[i-j]%M);
    }

    for (int i=0;i<=n-m;i++){
        r[i]=p2[i];
        for (int j=1;j<=i;j++) dec(r[i],1ll*h[j]*p2[i-j]%M);
    }
    */

    if (k == 0)
    {
        ans = p2[n];
        for (int i = 0; i <= n - m; i++)
            dec(ans, 1ll * p2[n - m - i] * r[i] % M);
        cout << ans << endl;
        return 0;
    }

    vi A(n - m + 1, 0);
    for (int i = 0; i <= n - m; i++)
        A[i] = r[i];
    vi B = fft::multiply_mod(A, A, M, 1);
    vi C(n - m + 1, 0);
    C[0] = 1;
    vi D(n - m + 1, 0);
    for (int i = 0; i <= n - m; i++)
        D[i] = h[i];
    k--;
    while (k)
    {
        if (k & 1)
        {
            vi tmp = fft::multiply_mod(C, D, M);
            for (int j = 0; j <= n - m; j++)
                C[j] = tmp[j];
        }
        vi tmp = fft::multiply_mod(D, D, M);
        for (int j = 0; j <= n - m; j++)
            D[j] = tmp[j];
        k >>= 1;
    }

    for (int i = 0; i <= n - m; i++)
        add(ans, 1ll * C[i] * B[n - (m + i)] % M);
    cout << ans << endl;
}