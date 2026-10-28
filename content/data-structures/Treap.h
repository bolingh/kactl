/**
 * Description: A short self-balancing tree. It acts as a
 *  sequential container with log-time splits/joins, and
 *  is easy to augment with additional data.
 * Time: $O(\log N)$
 */
mt19937 mt;
struct treap {
private:
    struct node {
        int pri, v, sum, tag, sz;
        node *l, *r;
        node(int x) : pri(mt()), v(x), sum(x), tag(0), sz(1) {l = r = 0;}
        void pull() {
            sum = v;
            sz = 1;
            for(auto &i : {l, r}) {
                if(i) sum += i -> sum + i -> tag * i -> sz, sz += i -> sz;
            }
        }
        void push() {
            if(!tag) return;
            v += tag;
            sum += tag * sz;
            for(auto &i : {l, r}) {
                if(i) i -> tag += tag;
            }
            tag = 0;
        }
    }*root = 0;
	
    int size(node *a) {return a? a -> sz : 0;}

    node* merge(node *a, node *b) {
        if(!a || !b) return a? a : b;
        a -> push(), b -> push();
        if(a -> pri > b -> pri) return a -> r = merge(a -> r, b), a -> pull(), a;
        else return b -> l = merge(a, b -> l), b -> pull(), b;
    }

    void split(node *nd, node* &a, node* &b, int k) {
        if(!nd) return a = b = 0, void();
        nd -> push();
        if(k <= size(nd -> l)) b = nd, split(nd -> l, a, b -> l, k);
        else a = nd, split(nd -> r, a -> r, b, k - size(nd -> l) - 1);
        nd -> pull();
    }
public:
    int size() {return size(root);}

    void insert(int x) {root = merge(root, new node(x));}

    int qry(int l, int r) {
        node *a, *b, *c;
        split(root, b, c, r);
        split(b, a, b, l - 1);
        int ans = b -> sum;
        root = merge(a, merge(b, c));
        return ans;
    }

    void upd(int l, int r, int x) {
        node *a, *b, *c;
        split(root, b, c, r);
        split(b, a, b, l - 1);
        b -> tag += x;
        root = merge(a, merge(b, c));
    }
};
