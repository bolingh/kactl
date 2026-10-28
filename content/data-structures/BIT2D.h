/*
 * Description: 1-based, [l, r]
*/
const int maxn = 305;
int bit[maxn][maxn];

int lowbit(int &x) {return x & -x;}

void upd(int x, int y, int k) {
    for(; x < maxn; x += lowbit(x)) {
        for(int ty = y; ty < maxn; ty += lowbit(ty)) bit[x][ty] += k;
    }
}

int qry(int x, int y) {
    int ans = 0;
    for(; x; x -= lowbit(x)) {
        for(int ty = y; ty; ty -= lowbit(ty)) ans += bit[x][ty];
    }
    return ans;
}

int qry(int x1, int y1, int x2, int y2) {
    if(x1 > x2) swap(x1, x2);
    if(y1 > y2) swap(y1, y2);
    return qry(x2, y2) - qry(x1 - 1, y2) - qry(x2, y1 - 1) + qry(x1 - 1, y1 - 1);
}