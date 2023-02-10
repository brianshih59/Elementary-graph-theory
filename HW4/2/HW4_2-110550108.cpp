//finding cut vertex
#include <bits/stdc++.h>
#define pb push_back
using namespace std;

vector<vector<int>> adj;
vector<int> found, low;
vector<bool> visited, isCutVertex;
int t = 0;

void dfs(int v, int parent){
    visited[v] = 1;
    int children = 0;
    found[v] = low[v] = ++t;
    for(int u: adj[v]){
        if(!visited[u]){
            ++children;
            dfs(u, v);
            low[v] = min(low[v], low[u]);   // й╣ж^ил
            if(parent != -1 && low[u] >= found[v] || parent == -1 && children >= 2)
                isCutVertex[v] = 1;
        }
        else if(u != parent)    // back edge
            low[v] = min(low[v], found[u]);
    }
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    adj.resize(n);
    found.resize(n);
    low.resize(n);
    visited.assign(n, 0);
    isCutVertex.assign(n, 0);
    for(int i = 0; i < m; i++){
        int u, v;
        cin >> u >> v;
        adj[--u].pb(--v);
        adj[v].pb(u);
    }
    dfs(0, -1);
    int ans = 0;
    for(int i = 0; i < n; i++)
        if(isCutVertex[i])
            ++ans;
    cout << ans << '\n';
    for(int i = 0; i < n; i++)
        if(isCutVertex[i])
            cout << i + 1 << " ";
    return 0;
}
