/**
 * Time: $O(V^2E)$
 */
struct dinic {
    struct edge {int to, cap, rev;};
    int n;
    vector<vector<edge>> v;
    vector<int> lvl, ptr;
    dinic(int _n) : n(_n) {
        v.resize(n);
        lvl.resize(n, -1);
        ptr.resize(n);
    }
    void add_edge(int x, int y, int c) {
        v[x].push_back({y, c, (int)v[y].size()});
        v[y].push_back({x, 0, (int)v[x].size() - 1});
    }
    bool bfs(int s, int t) {
        fill(lvl.begin(), lvl.end(), -1);
        queue<int> q;
        lvl[s] = 0;
        q.push(s);
        while(!q.empty()) {
            int cur = q.front();
            q.pop();
            for(auto &x : v[cur]) {
                if(lvl[x.to] == -1 && x.cap > 0) {
                    lvl[x.to] = lvl[cur] + 1;
                    q.push(x.to);
                }
            }
        }
        return lvl[t] != -1;
    }
    int dfs(int s, int t, int flow) {
        if(s == t) return flow;
        int ans = 0;
        for(int &i = ptr[s]; i < v[s].size(); ++i) {
            edge e = v[s][i];
            if(lvl[e.to] == lvl[s] + 1 && e.cap > 0) {
                int res = dfs(e.to, t, min(flow - ans, e.cap));
                if(res > 0) {
                    v[s][i].cap -= res, v[e.to][e.rev].cap += res;
                    ans += res;
                    if(ans == flow) break;
                }
            }
        }
        return ans;
    }
    int max_flow(int s, int t) {
        int ans = 0;
        while(bfs(s, t)) {
            fill(ptr.begin(), ptr.end(), 0);
            while(int tmp = dfs(s, t, INT_MAX)) ans += tmp;
        }
        return ans;
    }
    int get_flow(int id) {
        auto [u, idx] = edges[id];
        auto &e = v[u][idx];
        return v[e.to][e.rev].cap;
    }
};
