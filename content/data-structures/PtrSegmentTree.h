/*
 * Description: 1-based, [l, r] range sum. p.s. this template sucks, I forgot how yo use.
 * Time: O(\log n)
*/
const int maxn = 1e8 + 1;
#define m ((l + r) >> 1)

struct node {
    int v, tag;
    node *l, *r;
    node(int k = 0) {
        v = 0;
        tag = k;
        l = r = 0;
    }
    void pull() {v = (l? l -> v : 0) + (r? r -> v : 0);}
    void push(int _l, int _r) {
        if(!tag) return;
        if(_l == _r) {v += tag, tag = 0; return;}
        v += tag * (_r - _l + 1);
        if(!l) l = new node();
        if(!r) r = new node();
        l -> tag += tag, r -> tag += tag;
        tag = 0;
    }
};

int qry(node* &nd, int ql, int qr, int l = 1, int r = maxn) {
    if(!nd) return 0;
    nd -> push(l, r);
    if(ql > r || qr < l) return 0;
    if(ql <= l && qr >= r) return nd -> v;
    return qry(nd -> l, ql, qr, l, m) + qry(nd -> r, ql, qr, m + 1, r);
}

void upd(node* &nd, int ql, int qr, int k, int l = 1, int r = maxn) {
    if(!nd) nd = new node();
    nd -> push(l, r);
    if(ql > r || qr < l) return;
    if(ql <= l && qr >= r) {nd -> tag += k, nd -> push(l, r); return;}
    upd(nd -> l, ql, qr, k, l, m), upd(nd -> r, ql, qr, k, m + 1, r);
    nd -> pull();
}
