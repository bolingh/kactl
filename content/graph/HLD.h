/**
 * Usage: Query or add value to a payh or subtree
 */
const int maxn = 1e5 + 3;
vector<int> g[maxn];
int sz[maxn], dep[maxn], hson[maxn], fa[maxn];
int dfn[maxn], rnk[maxn], top[maxn];
int arr[maxn], seg[maxn << 2], tag[maxn << 2];
int t = 0;
int n, q, r, p; // p:=mod
#define m ((l + r) >> 1)
#define il i << 1
#define ir i << 1 | 1

void dfs1(int cur, int pre, int d) {
	fa[cur] = pre;
	dep[cur] = d;
	sz[cur] = 1;
	hson[cur] = -1;
	for(auto &x : g[cur]) {
		if(x == pre) continue;
		dfs1(x, cur, d + 1);
		sz[cur] += sz[x];
		if(hson[cur] == -1 || sz[x] > sz[hson[cur]]) hson[cur] = x;
	}
}

void dfs2(int cur, int head) {
	dfn[cur] = ++t;
	rnk[t] = cur;
	top[cur] = head;
	if(hson[cur] == -1) return;
	dfs2(hson[cur], head);
	for(auto &x : g[cur]) {
		if(x != hson[cur] && x != fa[cur]) dfs2(x, x);
	}
}

void pull(int &i) {seg[i] = (seg[il] + seg[ir]) % p;}

void push(int l, int r, int i) {
	if(tag[i] == 0) return;
	if(l == r) {
		(seg[i] += tag[i]) %= p;
		tag[i] = 0;
		return;
	}
	(seg[i] += (1LL * tag[i] * (r - l + 1))) %= p;
	(tag[il] += tag[i]) %= p, (tag[ir] += tag[i]) %= p;
	tag[i] = 0;
}

void build(int l = 1, int r = maxn, int i = 1) {
	if(l == r) return seg[i] = arr[rnk[l]], void();
	build(l, m, il), build(m + 1, r, ir);
	pull(i);
}

int qry(int ql, int qr, int l = 1, int r = maxn, int i = 1) {
	push(l, r, i);
	if(ql > r || qr < l) return 0;
	if(ql <= l && qr >= r) return seg[i];
	return (qry(ql, qr, l, m, il) + qry(ql, qr, m + 1, r, ir)) % p;
}

int qryPath(int u, int v) {
	int ans = 0;
	while(top[u] != top[v]) {
		if(dep[top[u]] < dep[top[v]]) swap(u, v);
		(ans += qry(dfn[top[u]], dfn[u])) %= p;
		u = fa[top[u]];
	}
	if(dep[u] > dep[v]) swap(u, v);
	(ans += qry(dfn[u], dfn[v])) %= p;
	return ans;
}

int qrySubtree(int u) {
	return qry(dfn[u], dfn[u] + sz[u] - 1);
}

void upd(int ql, int qr, int val, int l = 1, int r = maxn, int i = 1) {
	push(l, r, i);
	if(ql > r || qr < l) return;
	if(ql <= l && qr >= r) return (tag[i] += val) %= p, push(l, r, i), void();
	upd(ql, qr, val, l, m, il), upd(ql, qr, val, m + 1, r, ir);
	pull(i);
}

void updPath(int u, int v, int k) {
	while(top[u] != top[v]) {
		if(dep[top[u]] < dep[top[v]]) swap(u, v);
		upd(dfn[top[u]], dfn[u], k);
		u = fa[top[u]];
	}
	if(dep[u] > dep[v]) swap(u, v);
	upd(dfn[u], dfn[v], k);
}

void updSubtree(int u, int k) {
	upd(dfn[u], dfn[u] + sz[u] - 1, k);
}

/*
cin >> n >> q >> r >> p;
rep(i, 1, n + 1) cin >> arr[i];
rep(i, 0, n - 1) {
	int a, b;
	cin >> a >> b;
	g[a].pb(b), g[b].pb(a);
}
dfs1(r, -1, 0);
dfs2(r, r);
build();
*/
