/*
 * Description: 1-based, [l, r] range sum
 * Time: O(\log n)
*/
const int maxn = 2e5 + 1;
int arr[maxn], seg[maxn << 2], tag[maxn << 2];
#define m ((l + r) >> 1)

void pull(int &i) {seg[i] = seg[i << 1] + seg[i << 1 | 1];}

void push(int &l, int &r, int &i) {
    if(!tag[i]) return;
    if(l == r) return seg[i] += tag[i], tag[i] = 0, void();
    seg[i] += tag[i] * (r - l + 1);
    tag[i << 1] += tag[i], tag[i << 1 | 1] += tag[i];
    tag[i] = 0;
}

void build(int l = 1, int r = maxn, int i = 1) {
    if(l == r) return seg[i] = arr[l], void();
    build(l, m, i << 1); build(m + 1, r, i << 1 | 1);
    pull(i);
}

int qry(int ql, int qr, int l = 1, int r = maxn, int i = 1) {
    push(l, r, i);
    if(ql > r || qr < l) return 0;
    if(ql <= l && qr >= r) return seg[i];
    return qry(ql, qr, l, m, i << 1) + qry(ql, qr, m + 1, r, i << 1 | 1);
}

void upd(int ql, int qr, int k, int l = 1, int r = maxn, int i = 1) {
    push(l, r, i);
    if(ql > r || qr < l) return;
    if(ql <= l && qr >= r) return tag[i] += k, push(l, r, i), void();
    upd(ql, qr, k, l, m, i << 1), upd(ql, qr, k, m + 1, r, i << 1 | 1);
    pull(i);
}
#undef m
