#include <bits/stdc++.h>
using namespace std;
int main(){
    int n, m;
    cin >> n >> m;
    vector<vector<int>> a(n, vector<int>(n, 0));
    vector<pair<int, int>> deg(n, {0, 0});
    for(int i=0; i<m; i++){
        int u, v, w;
        cin >> u >> v >> w;
        u--, v--;
        a[u][v] = w;
        deg[u].second++;
        deg[v].first++;
    }
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++)
            cout << a[i][j] << " ";
        cout << endl;
    }
    for(auto [i, j]: deg)
        cout << i << " " << j << endl;
    return 0;
}
