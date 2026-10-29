const ll inf = 1e18;

// return {haveNegCycle, distance}
pair<bool, vector<ll>> SPFA(vector<vector<pii>>& g, int st) {
    int n = g.size();
    vector<ll> dis(n, inf);
    vector<int> cnt(n);
    vector<bool> inq(n);
    queue<int> q;
    dis[st] = 0;
    q.push(st);
    inq[st] = true;
    cnt[st] = 1;
    while(!q.empty()) {
        int cur = q.front();
        q.pop();
        inq[cur] = false;
        for(auto &e : g[cur]) {
            int to = e.f, w = e.s;
            if(dis[to] > dis[cur] + w) {
                dis[to] = dis[cur] + w;
                if(!inq[to]) {
                    q.push(to);
                    inq[to] = true;
                    if(++cnt[to] >= n) return {true, {}};
                }
            }
        }
    }
    return {false, dis};
}
