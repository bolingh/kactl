/**
 * Description: Find size of Minimun spanning tree.
 */
struct DSU {
private:
    vector<int> v;
public:
    DSU(int n) {v.assign(n + 1, -1);}
    int find(int x) {
        if(v[x] < 0) return x;
        return v[x] = find(v[x]);
    }
    bool chk(int x, int y) {return find(x) == find(y);}
    void merge(int x, int y) {
        int xroot = find(x), yroot = find(y);
        if(xroot == yroot) return;
        //merge y into x
        if(abs(v[xroot]) < abs(v[yroot])) swap(xroot, yroot);
        v[xroot] += v[yroot];
        v[yroot] = xroot;
    }
};

struct edge {int x, y, w;};

int kruskal(vector<edge> &v) {
    int n = v.size();
    sort(v.begin(), v.end(), [&](const edge a, const edge b) {
        return a.w < b.w;	
    });
    DSU dsu(n);
    int ans = 0;
    for(auto &i : v) {
        if(!dsu.chk(i.x, i.y)) {
            ans += i.w;
            dsu.merge(i.x, i.y);
        }
    }
    return ans;
}
