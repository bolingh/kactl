/*
 * Description: 0-based, [l, r] range sum
 * Time: O(\log n)
*/
vector<int> seg;
int sz;

void upd(int i, int k) { // set arr[i] to be k
    seg[i += sz] = k;
    for(i >>= 1; i; i >>= 1) {
        seg[i] = seg[i << 1] + seg[i << 1 | 1];
    }
}

int qry(int l, int r) {
    int ans = 0;
    for(l += sz, r += sz; l <= r; l >>= 1, r >>= 1) {
        if(l & 1) ans += seg[l++];
        if(~r & 1) ans += seg[r--];
    }
    return ans;
}

/*
cin >> n;
sz = 1;
while(sz < n) sz <<= 1;
seg.resize(sz << 1);
*/
