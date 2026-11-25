int n = nums.size();
int pr = 31;
vector<ll> mod = {(ll)1e9 + 7, (ll)1e9 + 9};
vector<vector<ll>> P(2, vector<ll>(n + 1)), H(2, vector<ll>(n + 1));
P[0][0] = P[1][0] = 1;
for(int i = 1; i <= n; ++i) {
    for(int t : {0, 1}) {
        P[t][i] = P[t][i - 1] * pr % mod[t];
        H[t][i] = (H[t][i - 1] * pr + nums[i - 1]) % mod[t];
    }
}
auto getHash = [&](int l, int r) {
    pair<ll, ll> res;
    res.first = (H[0][r + 1] - H[0][l] * P[0][r - l + 1] % mod[0] + mod[0]) % mod[0];
    res.second = (H[1][r + 1] - H[1][l] * P[1][r - l + 1] % mod[1] + mod[1]) % mod[1];
    return res;
};