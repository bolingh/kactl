#define vec vector
#define cp complex<double>
int rev(int x, const int &n) {
    int k, t;
    for(k = 0, t = 0; x || t < n; t++, x >>= 1) {
        k = (k << 1 | (x & 1));
    }
    return k;
}

void rev_array(vec<cp> &a) {
    int n = a.size(), r = log2(n);
    for(int i = 0; i < n; i++) {
        int x = rev(i, r);
        if(x > i) swap(a[i], a[x]);
    }
}

void FFT(vec<cp> &a, bool inv) {
    int n = a.size();
    rev_array(a);
    for(int m = 2; m <= n; m <<= 1) {
    	double ang = 2 * M_PI / m * (inv? -1 : 1);
    	cp wn(cos(ang), sin(ang));
    	for(int k = 0; k < n; k += m) {
            cp w = 1;
            int s = (m >> 1);
            for(int j = 0; j < s; j++, w *= wn) {
                cp t = w * a[k + j + s], u = a[k + j];
                a[k + j] = u + t;
                a[k + j + s] = u - t;
            }
        }
    }
    if(inv) {
        for(auto &i : a) i /= n;
    }
}

vec<int> mul(vec<int> a, vec<int> b) {
    if (a.empty() || b.empty()) return {};
    int sz = a.size() + b.size() - 1, n = 1;
    while (n < sz) n <<= 1;
    vec<cp> A(n), B(n);
    for (int i = 0; i < a.size(); i++) A[i] = a[i];
    for (int i = 0; i < b.size(); i++) B[i] = b[i];
    FFT(A, 0);
    FFT(B, 0);
    for (int i = 0; i < n; i++) A[i] *= B[i];
    FFT(A, 1);
    vec<int> ans(sz);
    for (int i = 0; i < sz; i++) {
        ans[i] = round(A[i].real());
    }
    return ans;
}
