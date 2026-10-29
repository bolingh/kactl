int n, q, t = 0;
const int root = 1;
vector<int> anc, tin, tout;
vector<vector<int>> v, child;

void init() {
    anc.resize(n + 1);
    tin.resize(n + 1), tout.resize(n + 1);
    v.resize(n + 1, vector<int>(30, -1));
    child.resize(n + 1);
}

void dfs(int cur) {
    tin[cur] = t++;
    for(auto &x : child[cur]) dfs(x);
    tout[cur] = t++;
}

void build() {
    for(int i = 2; i <= n; ++i) v[i][0] = anc[i];
    for(int i = 1; i < 30; ++i) {
        for(int j = 1; j <= n; ++j) {
            if(v[j][i - 1] != -1) v[j][i] = v[v[j][i - 1]][i - 1];
        }
    }
    dfs(root);
}

bool isanc(int &x, int &y) {
    return tin[x] <= tin[y] && tout[x] >= tout[y];
}

int lca(int &x, int &y) {
    if(isanc(x, y)) return x;
    if(isanc(y, x)) return y;
    int ans = x;
    for(int i = 29; ~i; --i) {
        if(v[ans][i] == -1) continue;
        if(!isanc(v[ans][i], y)) ans = v[ans][i];
    }
    return anc[ans];
}
