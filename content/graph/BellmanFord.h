/**
 * Time: O(VE)
 */
struct edge {int a, b, w;}; // a -> b, weight = w

// n = num of points, m = num of edges
int bellmanford(vector<edge> v, int n, int m, int st, int ed) {
    vector<int> ans(n, 1e9);
    ans[st] = 0;
    for(int t = 0; t < m - 1; t++) {
        for(auto &i : v) ans[i.b] = min(ans[i.b], ans[i.a] + i.w);
    }
    /*
    for(auto &i : v) {
        if(ans[i.b] > ans[i.a] + i.w) cout << "neg cycle\n";
	}
    */
    return ans[ed] == 1e9? -1 : ans[ed];
}

