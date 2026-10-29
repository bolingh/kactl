/**
 * Author: Simon Lindholm
 * Date: 2016-12-15
 * License: CC0
 * Source: http://en.wikipedia.org/wiki/Floyd–Warshall_algorithm
 * Description: Calculates all-pairs shortest path in a directed graph that might have negative edge weights.
 * Input is an distance matrix $m$, where $m[i][j] = \texttt{inf}$ if $i$ and $j$ are not adjacent.
 * As output, $m[i][j]$ is set to the shortest distance between $i$ and $j$, \texttt{inf} if no path,
 * or \texttt{-inf} if the path goes through a negative-weight cycle.
 * Time: O(N^3)
 * Status: slightly tested
 */
void floyd_warshall(vector<int> &v) {
    int n = v.size();
    for(int k = 0; k < n; k++) {
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) v[i][j] = min(v[i][j], v[i][k] + v[k][j]);
        }
    }
}

/*
int n, m, u, v, a, b, c;
cin >> n >> m >> x >> y; (0-based)
vector<vector<int>> v(n, vector<int>(n, (int)1e9));
for(int i = 0; i < n; i++) v[i][i] = 0;
while(m--) cin >> a >> b >> c, v[a][b] = c;
floyd_warshall(v);
cout << v[x][y];
*/

