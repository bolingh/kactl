const int mod = 1e9 + 7;

struct mtx {
    vector<vector<int>> v;
    mtx(int n = 1, int m = 1) {v.assign(n, vector<int>(m, 0));}
    
    mtx(vector<vector<int>> _v) {v = _v;}
    
    void I() { // make self identity
        if(!square()) return;
        for(auto &i : v) for(auto &j : i) j = 0;
        for(int i = 0; i < v.size(); i++) v[i][i] = 1;
    }
    
    mtx operator*(mtx a) {
        if(v.empty() || a.v.empty() || v[0].size() != a.v.size()) return *this;
        int n = v.size(), m = a.v[0].size(), k = a.v.size();
        mtx ans(n, m);
        for(int i = 0; i < n; i++)
            for(int j = 0; j < m; j++)
                for(int z = 0; z < k; z++)
                    (ans.v[i][j] += 1ll * v[i][z] * a.v[z][j] % mod) %= mod;
        return ans;
    }
    
    mtx pow(int t) {
        if(!square()) return *this;
        mtx x = *this;
        int n = v.size();
        mtx ans(n, n);
        ans.I();
        for(; t; t >>= 1, x = x * x) {
            if(t & 1) ans = ans * x;
        }
        return ans;
    }
};