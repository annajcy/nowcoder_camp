#ifndef WORKSPACE_TEMPLATE_H
#define WORKSPACE_TEMPLATE_H

// #define DEBUG
#include <bits/stdc++.h>

#include <bits/stdc++.h>

using ll = long long;

template <typename T>
constexpr T inv(T a, T moder)
{
    T b = moder, s = 1, t = 0;
    while (b)
    {
        T tmp = a, q = a / b;
        a = b, b = tmp % a;
        tmp = s;
        s = t;
        t = tmp - s * q;
    }
    assert(a == 1);
    return s < 0 ? s + moder : s;
}

template <typename T, typename U>
constexpr T norm(U value, T moder)
{
    if (value < -moder || value >= moder)
    {
        value %= moder;
    }
    value += value < 0 ? moder : 0;
    return value;
}

template <typename T>
constexpr T mult_mod(T a, T b, T moder)
{
    if constexpr (std::is_same_v<T, int>)
    {
        a = norm(1ll * a * b, moder);
    }
    else if constexpr (std::is_same_v<T, ll>)
    {
        ll q = ll((long double)a * b / moder);
        a = norm(a * b - q * moder, moder);
    }
    else
    {
        static_assert(std::is_same_v<T, int> || std::is_same_v<T, ll>, "Unsupported type");
    }
    return a;
}

template <typename T, typename U>
constexpr T powermod(T a, U exp, T moder)
{
    assert(exp >= 0);
    T ret = 1;
    for (; exp > 0; exp >>= 1)
    {
        if (exp & 1)
            ret = mult_mod(ret, a, moder);
        a = mult_mod(a, a, moder);
    }
    return ret;
}

template <auto moder>
class Mod
{
public:
    using T = decltype(moder);
    T a;
    static constexpr T moder_expose = moder;

    Mod() : a() {}

    template <typename U>
    Mod(const U &u) { a = norm(u, moder); }

    Mod &operator+=(const Mod &u)
    {
        a += u.a;
        a -= a >= moder ? moder : 0;
        return *this;
    }
    Mod &operator-=(const Mod &u)
    {
        a -= u.a;
        a += a < 0 ? moder : 0;
        return *this;
    }
    Mod &operator++() { return *this += 1; }
    Mod &operator--() { return *this -= 1; }
    Mod operator++(int)
    {
        Mod result = *this;
        *this += 1;
        return result;
    }
    Mod operator--(int)
    {
        Mod result = *this;
        *this -= 1;
        return result;
    }
    Mod operator-() const { return Mod(-a); }
    Mod &operator*=(const Mod &u)
    {
        a = mult_mod(a, u.a, moder);
        return *this;
    }
    Mod &operator/=(const Mod &u) { return *this *= inv(u.a, moder); }
    explicit operator bool() const { return a; }

    template <typename U>
    Mod power(U exp) const
    {
        return Mod(powermod(a, exp, moder));
    }
};

template <auto moder>
Mod<moder> operator+(const Mod<moder> &u, const Mod<moder> &v) { return Mod<moder>(u) += v; }
template <auto moder, typename U>
Mod<moder> operator+(const U &u, const Mod<moder> &v) { return Mod<moder>(u) += v; }
template <auto moder, typename U>
Mod<moder> operator+(const Mod<moder> &u, const U &v) { return Mod<moder>(u) += v; }
template <auto moder>
Mod<moder> operator-(const Mod<moder> &u, const Mod<moder> &v) { return Mod<moder>(u) -= v; }
template <auto moder, typename U>
Mod<moder> operator-(const U &u, const Mod<moder> &v) { return Mod<moder>(u) -= v; }
template <auto moder, typename U>
Mod<moder> operator-(const Mod<moder> &u, const U &v) { return Mod<moder>(u) -= v; }
template <auto moder>
Mod<moder> operator*(const Mod<moder> &u, const Mod<moder> &v) { return Mod<moder>(u) *= v; }
template <auto moder, typename U>
Mod<moder> operator*(const U &u, const Mod<moder> &v) { return Mod<moder>(u) *= v; }
template <auto moder, typename U>
Mod<moder> operator*(const Mod<moder> &u, const U &v) { return Mod<moder>(u) *= v; }
template <auto moder>
Mod<moder> operator/(const Mod<moder> &u, const Mod<moder> &v) { return Mod<moder>(u) /= v; }
template <auto moder, typename U>
Mod<moder> operator/(const U &u, const Mod<moder> &v) { return Mod<moder>(u) /= v; }
template <auto moder, typename U>
Mod<moder> operator/(const Mod<moder> &u, const U &v) { return Mod<moder>(u) /= v; }
template <auto moder>
bool operator==(const Mod<moder> &u, const Mod<moder> &v) { return u.a == v.a; }
template <auto moder, typename U>
bool operator==(const U &u, const Mod<moder> &v) { return Mod<moder>(u).a == v.a; }
template <auto moder, typename U>
bool operator==(const Mod<moder> &u, const U &v) { return u.a == Mod<moder>(v).a; }
template <auto moder>
bool operator!=(const Mod<moder> &u, const Mod<moder> &v) { return u.a != v.a; }
template <auto moder, typename U>
bool operator!=(const U &u, const Mod<moder> &v) { return Mod<moder>(u).a != v.a; }
template <auto moder, typename U>
bool operator!=(const Mod<moder> &u, const U &v) { return u.a != Mod<moder>(v).a; }

template <typename U, auto moder>
U &operator<<(U &ostream, const Mod<moder> &u)
{
    return ostream << u.a;
}

template <typename U, auto moder>
U &operator>>(U &istream, Mod<moder> &u)
{
    typename Mod<moder>::T x;
    istream >> x;
    u = x;
    return istream;
}

#include <bits/stdc++.h>

template <typename T, auto U, auto... V>
class MultiArrayClass
{
public:
    using MultiArray = std::array<typename MultiArrayClass<T, V...>::MultiArray, U>;
};

template <typename T, auto U>
class MultiArrayClass<T, U>
{
public:
    using MultiArray = std::array<T, U>;
};

template <typename T, auto U, auto... V>
using MultiArray = typename MultiArrayClass<T, U, V...>::MultiArray;

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

const int moder = 998'244'353;
using Mint = Mod<moder>;

pii operator+(const pii &p1, const int &p2)
{
    return {p1.first + p2, p1.second};
}

namespace BM
{
    std::vector<Mint> BM(std::vector<Mint> s)
    {
        std::vector<Mint> C(1, 1), B(1, 1);
        int l = 0, m = 1;
        Mint b = 1;
        for (int n = 0; n < s.size(); ++n)
        {
            Mint d = 0;
            for (int i = 0; i <= l; ++i)
            {
                d += C[i] * s[n - i];
            }
            if (!d)
                ++m;
            else
            {
                std::vector<Mint> T = C;
                Mint c = -d / b;
                while (C.size() < B.size() + m)
                    C.push_back(0);
                for (int i = 0; i < B.size(); ++i)
                {
                    C[i + m] += c * B[i];
                }
                if (l * 2 <= n)
                {
                    l = n + 1 - l, B = T, b = d, m = 1;
                }
                else
                {
                    ++m;
                }
            }
        }
        return C;
    }
}

class Solver
{
public:
    constexpr static inline int BASE = 10;
    constexpr static inline int BASE2 = BASE * BASE;
    constexpr static inline int BASE3 = BASE2 * BASE;
    constexpr static inline unsigned STATE_NUM = 1u << (BASE - 1);
    constexpr static inline int LEN = 100;
    constexpr static inline int LEN_MAX = 1'000'010;
    constexpr static inline int MIDDLE_LEFT = BASE2 - BASE + 1;
    constexpr static inline int RIGHT = BASE - 1;
    constexpr static inline int KEY_STATES[] = {1, 2, 4, 8, 12, 16, 18, 24, 28, 32, 48, 64, 96, 128, 256};

    class State
    {
    public:
        Mint shift;
        std::array<pii, RIGHT> value, pre, suf;

        void gen_pre_suf()
        {
            for (int i = 0; i < RIGHT; ++i)
            {
                pre[i] = value[i];
                if (i > 0)
                {
                    pre[i] = merge(pre[i], pre[i - 1]);
                }
            }
            for (int i = RIGHT - 1; i >= 0; --i)
            {
                suf[i] = value[i];
                if (i < RIGHT - 1)
                {
                    suf[i] = merge(suf[i], suf[i + 1]);
                }
            }
        }

        pii query(pii p) const
        {
            if (p.first == -1)
            {
                return {-1, -1};
            }
            auto [v, pos] = p;
            if (pos < RIGHT - 1)
            {
                return merge(pre[pos] + v, suf[pos + 1] + v + 1);
            }
            return pre[RIGHT - 1] + v;
        }
    };

    std::vector<MultiArray<State, LEN>> f;
    std::array<int, STATE_NUM> key_state_id, repr_state, repr_state_id;
    std::unique_ptr<MultiArray<Mint, std::size(KEY_STATES), LEN_MAX>> shifts;

    Solver() : f(STATE_NUM), key_state_id(), repr_state(), repr_state_id()
    {
        for (int i = 0; i < std::size(KEY_STATES); ++i)
        {
            key_state_id[KEY_STATES[i]] = i;
        }
        for (int i = 1; i < STATE_NUM; ++i)
        {
            for (auto u : KEY_STATES)
            {
                if (u <= i)
                {
                    repr_state[i] = u;
                    repr_state_id[i] = key_state_id[u];
                }
            }
        }
        shifts = std::make_unique<decltype(shifts)::element_type>();
    }

    template <typename T>
    static unsigned get_bits(T n)
    {
        unsigned state = 0;
        for (; n > 0; n /= BASE)
        {
            state |= 1u << (n % BASE);
        }
        return state & ~1u;
    }

    static pii merge(const pii &p1, const pii &p2)
    {
        if (p1.first != p2.first)
        {
            return std::min(p1, p2);
        }
        return std::max(p1, p2);
    }

    static void merge(const State &s1, const State &s2, State &result)
    {
        result.shift = s1.shift + s2.shift;
        assert(s2.value[0] != pii(-1, -1));
        auto min = std::numeric_limits<int>::max();
        for (int i = 0; i < RIGHT; ++i)
        {
            result.value[i] = s2.query(s1.value[i]);
            if (result.value[i].first != -1)
            {
                min = std::min(result.value[i].first, min);
            }
        }
        result.shift += min;
        for (int i = 0; i < RIGHT; ++i)
        {
            if (result.value[i].first != -1)
            {
                result.value[i].first -= min;
            }
        }
        result.gen_pre_suf();
    }

    static std::vector<int> trans(const std::string &ori, int length)
    {
        length = std::max(length, 4) + 2;
        std::vector<int> result(length);
        for (int i = 0; i < int(ori.size()); ++i)
        {
            result[length + i - int(ori.size())] = ori[i] - '0';
        }
        return result;
    }

    static void add(std::vector<int> &vec, int shift)
    {
        int n = vec.size();
        vec[n - 4] += shift;
        for (int i = n - 1; i > 0; --i)
        {
            if (vec[i] >= BASE)
            {
                vec[i] -= BASE;
                ++vec[i - 1];
            }
            else if (vec[i] < 0)
            {
                vec[i] += BASE;
                --vec[i - 1];
            }
        }
    }

    static std::vector<unsigned> get_state(std::vector<int> vec, int shift)
    {
        int n = vec.size();
        add(vec, shift);
        std::vector<unsigned> result(n);
        unsigned state = 0;
        for (int i = 0; i < n; ++i)
        {
            state |= 1u << vec[i];
            result[i] = state;
        }
        return result;
    }

    static std::vector<int> bfs(int size, const std::vector<int> &start, const std::function<unsigned(int)> &get_state)
    {
        std::vector<int> dis(size, -1);
        std::queue<int> queue;
        for (auto u : start)
        {
            dis[u] = 0;
            queue.emplace(u);
        }
        while (!queue.empty())
        {
            int u = queue.front();
            queue.pop();
            auto check = [&](int num)
            {
                if (num < 0 || num >= size)
                {
                    return;
                }
                if (dis[num] != -1)
                {
                    return;
                }
                dis[num] = dis[u] + 1;
                queue.emplace(num);
            };
            unsigned state = get_state(u);
            for (int k = 1; k < BASE; ++k)
            {
                if (state >> k & 1)
                {
                    check(u + k);
                    check(u - k);
                }
            }
        }
        return dis;
    }

    std::optional<Mint> calc(const std::string &x_ori, const std::string &y_ori)
    {
        if (x_ori == "0")
        {
            if (y_ori == "0")
            {
                return 0;
            }
            return std::nullopt;
        }
        auto x = trans(x_ori, y_ori.size()), y = trans(y_ori, y_ori.size());
        int n = x.size();
        std::vector<unsigned> state_x[4];
        for (int i = 0; i < 4; ++i)
        {
            state_x[i] = get_state(x, i - 1);
        }
        auto state_y = get_state(y, 0);
        std::vector<unsigned> state0;
        int x_remain = x[n - 3] * BASE2 + x[n - 2] * BASE + x[n - 1];
        int y_remain = y[n - 3] * BASE2 + y[n - 2] * BASE + y[n - 1];
        auto dis = bfs(BASE2 + 2 * BASE3 + BASE, {BASE2 + x_remain}, [&](int u)
                       {
            int real = u + BASE3 - BASE2;
            return state_x[real / BASE3][n - 4] | get_bits(real % BASE3); });
        auto x_1 = x;
        add(x_1, 1);
        auto check_high_equal = [&](const std::vector<int> &vec1, const std::vector<int> &vec2)
        {
            for (int i = 0; i <= n - 4; ++i)
            {
                if (vec1[i] != vec2[i])
                {
                    return false;
                }
            }
            return true;
        };
        if (check_high_equal(x, y))
        {
            int ans = dis[BASE2 + y_remain];
            if (ans == -1)
            {
                return {};
            }
            return ans;
        }
        if (check_high_equal(x_1, y))
        {
            return dis[BASE2 + BASE3 + y_remain];
        }
        x = x_1;
        Mint shift = dis[BASE2 + 2 * BASE3];
        int split = -1;
        for (int i = 0; i < RIGHT; ++i)
        {
            if (i == RIGHT - 1 || dis[BASE2 + 2 * BASE3 + i] != dis[BASE2 + 2 * BASE3 + i + 1])
            {
                if (i < RIGHT - 1)
                {
                    assert(dis[BASE2 + 2 * BASE3 + i] + 1 == dis[BASE2 + 2 * BASE3 + i + 1]);
                }
                for (int j = i + 1; j < RIGHT - 1; ++j)
                {
                    assert(dis[BASE2 + 2 * BASE3 + j] == dis[BASE2 + 2 * BASE3 + j + 1]);
                }
                split = i;
                break;
            }
        }
        auto update = [&](unsigned state, int len)
        {
            pii result;
            State *ptr;
            if (len < LEN)
            {
                ptr = &f[state][len];
            }
            else
            {
                int temp_len = len - (len - LEN / 2) / 9 * 9;
                ptr = &f[repr_state[state]][temp_len];
            }
            result = ptr->query({0, split});
            shift += result.first;
            if (len < LEN)
            {
                shift += f[state][len].shift;
            }
            else
            {
                shift += (*shifts)[repr_state_id[state]][len];
            }
            split = result.second;
        };
        for (int i = 0; i < n; ++i)
        {
            if (x[i] != y[i])
            {
                for (int j = n - 4; j > i; --j)
                {
                    for (int k = x[j] + 1; k < BASE; ++k)
                    {
                        update((state_x[2][j - 1] | 1u << k) >> 1, n - 1 - j);
                    }
                }
                for (int j = x[i] + 1; j < y[i]; ++j)
                {
                    unsigned state = i == 0 ? 0u : state_x[2][i - 1];
                    state = (state | 1u << j) >> 1;
                    update(state, n - 1 - i);
                }
                for (int j = i + 1; j <= n - 4; ++j)
                {
                    for (int k = 0; k < y[j]; ++k)
                    {
                        update((state_y[j - 1] | 1u << k) >> 1, n - 1 - j);
                    }
                }
                std::vector<int> start;
                for (int j = 0; j <= split; ++j)
                {
                    start.emplace_back(j);
                }
                auto get_state = [&](int u)
                {
                    return state_y[n - 4] | get_bits(u);
                };
                dis = bfs(BASE3, start, get_state);
                int ans = dis[y_remain];
                if (split + 1 < RIGHT)
                {
                    start.clear();
                    for (int j = split + 1; j < RIGHT; ++j)
                    {
                        start.emplace_back(j);
                    }
                    dis = bfs(BASE3, start, get_state);
                    ans = std::min(ans, dis[y_remain] + 1);
                }
                return shift + ans;
            }
        }
        return {};
    }

    void pre_calc_g()
    {
        for (unsigned state = 0; state < STATE_NUM; ++state)
        {
            MultiArray<int, RIGHT, RIGHT> arr;
            for (int i = 0; i < RIGHT; ++i)
            {
                auto dis = bfs(BASE3 + RIGHT, {i}, [&](int u)
                               { return get_bits(u) | state << 1; });
                for (int j = BASE3; j < BASE3 + RIGHT; ++j)
                {
                    arr[i][j - BASE3] = dis[j];
                }
#ifdef DEBUG
                if (state == 0u)
                {
                    for (int j = BASE3; j < BASE3 + RIGHT; ++j)
                    {
                        std::cerr << dis[j] << " \n"[j == BASE3 + RIGHT - 1];
                    }
                }
#endif
            }
            auto min = std::numeric_limits<int>::max();
            for (int i = 0; i < RIGHT; ++i)
            {
                for (int j = 0; j < RIGHT; ++j)
                {
                    if (arr[i][j] != -1)
                    {
                        min = std::min(min, arr[i][j]);
                    }
                }
            }
            auto &dp = f[state][3];
            dp.shift = min;
            for (int i = 0; i < RIGHT; ++i)
            {
                if (arr[i].front() == -1)
                {
                    dp.value[i] = {-1, -1};
                }
                else
                {
                    dp.value[i].first = arr[i][0] - min;
                    for (int j = 0; j < RIGHT; ++j)
                    {
                        if (j == RIGHT - 1 || arr[i][j] != arr[i][j + 1])
                        {
                            if (j < RIGHT - 1)
                            {
                                assert(arr[i][j] + 1 == arr[i][j + 1]);
                            }
                            for (int k = j + 1; k < RIGHT - 1; ++k)
                            {
                                assert(arr[i][k] == arr[i][k + 1]);
                            }
                            dp.value[i].second = j;
                            break;
                        }
                    }
                }
            }
            dp.gen_pre_suf();
        }
    }

    void pre_calc_f()
    {
        for (int len = 3; len < LEN - 1; ++len)
        {
            for (unsigned state = 0; state < STATE_NUM; ++state)
            {
                f[state][len + 1] = f[state][len];
                for (int d = 1; d < BASE; ++d)
                {
                    merge(f[state][len + 1], f[state | 1u << (d - 1)][len], f[state][len + 1]);
                }
#ifdef DEBUG
                if (len > 16)
                {
                    if (f[state][len].value != f[state][len - 9].value)
                    {
                        std::cerr << "Bad" << state << " " << len << "\n";
                        assert(false);
                    }
                }
                if (state == 0u)
                {
                    std::cerr << "----------------------\n";
                    for (int i = 0; i < BASE; ++i)
                    {
                        auto [p, v] = f[state][len].value[i];
                        std::cerr << p << " " << v << "\n";
                    }
                }
                if (state > 0 && (f[state][len].value != f[state - 1][len].value ||
                                  f[state][len].shift != f[state - 1][len].shift))
                {
                    std::cerr << "Len " << len << " Bad " << state << "\n";
                }
#endif
            }
        }
    }

    void pre_calc_shifts()
    {
        for (auto state : KEY_STATES)
        {
            std::vector<Mint> vec;
            for (int i = 17; i < LEN; ++i)
            {
                vec.emplace_back(f[state][i].shift);
            }
            vec = BM::BM(vec);
#ifdef DEBUG
            std::cerr << "State " << state << ", period " << vec.size() << "\n";
            for (auto u : vec)
            {
                std::cerr << u << " ";
            }
            std::cerr << "\n";
            std::cerr << "Example: f[" << state << "][" << LEN - 1 << "] = " << f[state][LEN - 1].shift << "\n";
#endif
            /// The first several items should be manually calculated
            /// But better not use them in the calculation in the final answer!
            /// Because the first several items might be wrong
            int id = key_state_id[state];
            auto &shift_arr = (*shifts)[id];
            for (int len = 3; len < LEN; ++len)
            {
                shift_arr[len] = f[state][len].shift;
            }
            /// The other items should be calculated by recurrence
            int sz = int(vec.size());
            assert(sz <= 18); /// Otherwise the answer cannot fit in ull
            for (int len = LEN; len < LEN_MAX; ++len)
            {
                unsigned long long accumulator = 0;
                for (int i = 1; i < sz; ++i)
                {
                    accumulator += 1ll * shift_arr[len - i].a * vec[i].a;
                }
                accumulator %= moder;
                int x = int(accumulator);
                shift_arr[len] = moder - x;
            }
        }
    }

    void solve()
    {
        pre_calc_g();
        pre_calc_f();
        pre_calc_shifts();
        int test;
        std::cin >> test;
        while (test--)
        {
            std::string x, y;
            std::cin >> x >> y;
            auto dis = calc(x, y);
            if (!dis)
            {
                std::cout << "-1\n";
            }
            else
            {
                std::cout << dis.value() << "\n";
            }
        }
    }
};

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    int test = 1;
    // std::cin >> test;
    // floating point number output template
    std::cout << std::fixed << std::setprecision(18);
    while (test--)
    {
        Solver solver;
        solver.solve();
    }
    return 0;
}

#undef DEBUG
#endif // WORKSPACE_TEMPLATE_H