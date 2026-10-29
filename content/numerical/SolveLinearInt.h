const int mod = 1e9 + 7;

int fpow(int x, int y) {
    int r = 1;
    for(; y; y >>= 1, x = 1LL * x * x % mod) {
        if(y & 1) r = 1LL * r * x % mod;
    }
    return r;
}

int inv(int x) {
    return fpow(x, mod - 2);
}

int dvd(int a, int b) {return 1LL * a * inv(b) % mod;}

struct mtx {
    int n, m, result;
    vector<vector<int>> M;
    mtx(int _n, int _m) : n(_n), m(_m) { // n by m
        M.resize(n, vector<int>(m));
    }
    int zeroCol, zeroRow;
    set<int> free;
    int guassian_elimination() {
        // 0: no sol, 1: 1 sol, 2: inf sol
        zeroCol = 0;
        for(int col = 0; col < m; ++col) {
            int i = col - zeroCol, p = i;
            while(p < n && M[p][col] == 0) ++p;
            if(p == n) {
                ++zeroCol;
                free.insert(col);
                continue;
            }
            if(p != i) swap(M[p], M[i]);
            // pivot: M[i][col]
            int d = M[i][col];
            vector<int> minus(n);
            for(int k = 0; k < n; ++k) {
                if(k == i) {
                    M[k][col] = 1;
                    continue;
                }
                minus[k] = dvd(M[k][col], d);
                M[k][col] = 0;
            }
            for(int j = col + 1; j < m; ++j) {
                int tmp = M[i][j];
                for(int k = 0; k < n; ++k) {
                    if(k == i) {
                        M[k][j] = dvd(M[k][j], d);
                    }
                    else {
                        M[k][j] -= 1LL * minus[k] * tmp % mod;
                        while(M[k][j] < 0) M[k][j] += mod;
                    }
                }
            }
        }
        for(int i = n - 1; i >= 0; --i) {
            bool isZeroRow = true;
            for(int j = 0; j < m - 1; ++j) {
                if(M[i][j] != 0) {
                    isZeroRow = false;
                    break;
                }
            }
            if(isZeroRow && M[i][m - 1] != 0) return result = -1;
            if(!isZeroRow) break;
        }
        int p = n - 1;
        while(p >= 0 && *max_element(M[p].begin(), M[p].end()) == 0 && *min_element(M[p].begin(), M[p].end()) == 0) --p;
        zeroRow = n - p - 1;
        if(n - zeroRow < m - 1) return result = 2;
        return result = 1;
    }
    void printSol() {
        int t = 0;
        for(int i = 0; i < m - 1; ++i) {
            if(free.count(i)) cout << 0 << ' ', ++t;
            else cout << M[i - t][m - 1] << ' ';
        }
    }
};
