/**
 * Description: 1-based, [l, r], range max
 * Time: build O(n\log n); qry O(1)
 */
const int maxn = 2e5 + 1;
int st[maxn][31];

void build() {
    for(int i = 1; i < 31; i++) {
        for(int j = 1; j + (1 << i) - 1 < maxn; j++) {
            st[j][i] = max(st[j][i - 1], st[j + (1 << (i - 1))][i - 1]);
        }
    }
}

int qry(int l, int r) {
    int k = log2(r - l + 1);
    return max(st[l][k], st[r - (1 << k) + 1][k]);
}

// for(int i = 1; i <= n; i++) cin >> st[i][0];