#define vec vector

const int p = 998244353, r = 3;

int fpow(int x, int y) {
    int ans = 1;
    for(; y; y >>= 1, x = 1LL * x * x % p) {
        if(y & 1) ans = 1LL * ans * x % p;
    }
    return ans;
}

int rev(int x, const int &n) {
    int k, t;
    for(k = t = 0; x || t < n; t++, x >>= 1) k = (k << 1 | (x & 1));
    return k;
}

void rev_array(vec<int> &v) {
    int n = v.size(), l = log2(n);
    for(int i = 0; i < n; i++) {
        int x = rev(i, l);
        if(x > i) swap(v[i], v[x]);
    }
}

void NTT(vec<int> &a, bool inv) {
    int n = a.size();
    rev_array(a);
    for(int m = 2; m <= n; m <<= 1) {
        int gn = fpow(r, (p - 1) / m);
        for(int k = 0; k < n; k += m) {
            int g = 1, s = (m >> 1);
            for(int j = 0; j < s; j++, g = 1LL * g * gn % p) {
                int t = 1LL * g * a[k + j + s] % p, u = a[k + j];
                a[k + j] = (u + t) % p;
                a[k + j + s] = (u - t + p) % p;
            }
        }
    }
    if(inv) {
        reverse(a.begin() + 1, a.end());
        int v = fpow(n, p - 2);
        for(auto &i : a) i = 1LL * i * v % p;
    }
}

vec<int> mul(vec<int> a, vec<int> b) {
    if (a.empty() || b.empty()) return {};
    int sz = a.size() + b.size() - 1, n = 1;
    while (n < sz) n <<= 1;
    a.resize(n), b.resize(n);
    NTT(a, 0);
    NTT(b, 0);
    for (int i = 0; i < n; i++) a[i] = 1LL * a[i] * b[i] % mod;
    NTT(a, 1);
    a.resize(sz);
	return a;
}
