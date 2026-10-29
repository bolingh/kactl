#define pii pair<int, int>
#define f first
#define s second

vector<int> dijkstra(vector<vector<pii>> &v, int &st) { // graph, start
    // v[i].f --> point, v[i].s --> weight
    int n = v.size();
    vector<int> ans(n, INT_MAX);
    vector<bool> vst(n);
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    //pq.top().f --> weight, pq.top().s --> point
    ans[st] = 0;
    pq.push({0, st});
    while(!pq.empty()) {
        int x = pq.top().s; pq.pop();
        if(vst[x]) continue;
        vst[x] = 1;
        for(auto &i : v[x]) {
            if(ans[x] + i.s < ans[i.f]) {
                ans[i.f] = ans[x] + i.s;
                pq.push({ans[i.f], i.f});
            }
        }
    }
    return ans;
}
