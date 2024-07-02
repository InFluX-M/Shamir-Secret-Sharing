#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;

struct mint
{
    ll v;
    int MOD;

    explicit operator ll() const { return v; }
    explicit operator int() const { return v; }
    mint() : v(0), MOD(1) {} // Default MOD set to 1, change as per requirement
    mint(ll _v, int _MOD) : MOD(_MOD)
    {
        v = (-MOD < _v && _v < MOD) ? _v : _v % MOD;
        if (v < 0)
            v += MOD;
    }

    friend bool operator==(const mint &a, const mint &b) { return a.v == b.v && a.MOD == b.MOD; }
    friend bool operator!=(const mint &a, const mint &b) { return !(a == b); }
    friend bool operator<(const mint &a, const mint &b) { return a.v < b.v; }
    friend bool operator>(const mint &a, const mint &b) { return a.v > b.v; }
    friend bool operator<=(const mint &a, const mint &b) { return a.v <= b.v; }
    friend bool operator>=(const mint &a, const mint &b) { return a.v >= b.v; }

    friend mint operator+(mint a, const mint &b) { return a += b; }
    friend mint operator-(mint a, const mint &b) { return a -= b; }
    friend mint operator*(mint a, const mint &b) { return a *= b; }
    friend mint operator/(mint a, const mint &b) { return a /= b; }

    mint &operator+=(const mint &m)
    {
        assert(MOD == m.MOD);
        if ((v += m.v) >= MOD)
            v -= MOD;
        return *this;
    }
    mint &operator-=(const mint &m)
    {
        assert(MOD == m.MOD);
        if ((v -= m.v) < 0)
            v += MOD;
        return *this;
    }
    mint &operator*=(const mint &m)
    {
        assert(MOD == m.MOD);
        v = v * m.v % MOD;
        return *this;
    }
    mint &operator/=(const mint &m)
    {
        assert(MOD == m.MOD);
        return (*this) *= inv(m);
    }

    mint operator-() const { return mint(-v, MOD); }
    mint &operator++()
    {
        v++;
        if (v >= MOD)
            v -= MOD;
        return *this;
    }
    mint &operator--()
    {
        v--;
        if (v < 0)
            v += MOD;
        return *this;
    }
    mint operator++(int)
    {
        mint temp(*this);
        v++;
        if (v >= MOD)
            v -= MOD;
        return temp;
    }
    mint operator--(int)
    {
        mint temp(*this);
        v--;
        if (v < 0)
            v += MOD;
        return temp;
    }

    friend mint pow(mint a, ll b)
    {
        assert(b >= 0);
        mint res(1, a.MOD);
        while (b)
        {
            if (b & 1)
            {
                res *= a;
            }
            a *= a;
            b >>= 1;
        }
        return res;
    }
    friend mint inv(const mint &a)
    {
        assert(a.v != 0);
        return pow(a, a.MOD - 2);
    }
};

vector<mint> poly;
vector<mint> shares;

vector<mint> make_poly(int t, mint s, int MOD)
{
    vector<mint> poly;
    poly.push_back(s);
    for (int i = 1; i < t; i++)
        poly.push_back(mint(rand(), MOD));
    mint last;
    while ((last = mint(rand(), MOD)) == mint(0, MOD))
        ;
    poly.push_back(last);
    return poly;
}

vector<mint> share_production(int n, int t, int MOD)
{
    bool valid = false;
    while (!valid)
    {
        valid = true;
        shares.clear();
        for (int i = 1; i <= n; i++)
        {
            mint res = mint(0, MOD);
            for (int j = t - 1; j >= 0; j--)
            {
                res *= mint(i, MOD);
                res += poly[j];
            }
            if (res == mint(0, MOD))
            {
                valid = false;
                poly = make_poly(t, poly[0], MOD);
                break;
            }
            shares.push_back(res);
        }
    }
    return shares;
}

mint secret_discovery(set<int> idxs, int t, int MOD)
{
    mint res = mint(0, MOD);
    for (int u : idxs)
    {
        mint x = shares[u - 1];
        mint ans = mint(1, MOD);
        for (int v : idxs)
        {
            if (u == v)
                continue;
            mint a = mint(v, MOD);
            mint b = mint(v - u, MOD);
            b = inv(b);
            ans *= a * b;
        }
        res += x * ans;
    }
    return res;
}

int32_t main()
{
    int s_t, t, n, MOD;
    cin >> s_t >> t >> n >> MOD;

    mint secret = mint(s_t, MOD);
    poly = make_poly(t, secret, MOD);
    shares = share_production(n, t, MOD);

    set<int> idxs;
    while (idxs.size() < t)
        idxs.insert((rand() % n) + 1);

    cout << secret_discovery(idxs, t, MOD).v;

    return 0;
}
