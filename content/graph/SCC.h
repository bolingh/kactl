struct scc {
    int n, t, scc_cnt;
    vector<vector<int>> v;
    vector<int> low, dfn, root;
    vector<bool> inStack;
    stack<int> st;
    scc(int _n) : n(_n), t(1), scc_cnt(0) {
        v.resize(n);
        low.resize(n);
        dfn.resize(n, -1);
        root.resize(n);
        inStack.resize(n);
    }
    void add_edge(int a, int b) {
        v[a].push_back(b);
    }
    void dfs(int cur) {
        low[cur] = dfn[cur] = t++;
        st.push(cur);
        inStack[cur] = true;
        for(auto &x : v[cur]) {
            if(dfn[x] == -1) {
                dfs(x);
                low[cur] = min(low[cur], low[x]);
            }
            else if(inStack[x]) low[cur] = min(low[cur], dfn[x]);
        }
        if(dfn[cur] == low[cur]) {
            ++scc_cnt;
            while(1) {
                int x = st.top();
                st.pop();
                root[x] = scc_cnt;
                inStack[x] = false;
                if(x == cur) break;
            }
        }
    }
    void tarjan(int l, int r) {
        for(int i = l; i <= r; ++i) {
            if(dfn[i] == -1) dfs(i);
        }
    }
};
