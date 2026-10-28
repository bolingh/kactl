/**
 * Description: 1-based, [l, r]
 * Time: $O(\log N)$
 */
const int maxn = 2e5 + 1;
int bit[maxn];

int lowbit(int &x) {return x & -x;}

void upd(int x, int k) {
    for(; x < maxn; x += lowbit(x)) bit[x] += k;
}

int qry(int x) {
    int ans = 0;
    for(; x; x -= lowbit(x)) ans += bit[x];
    return ans;
}

int qry(int l, int r) {return qry(r) - qry(l - 1);}