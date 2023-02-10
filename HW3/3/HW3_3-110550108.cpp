#include <bits/stdc++.h>
using namespace std;

vector<int> height, parent;
vector<vector<int>> adj;

int getHeight(int node){
    if(height[node])
        return height[node];
    if(adj[node].empty())
        return 0;
    int h = 0;
    for(int i: adj[node])
        h = max(h, getHeight(i));
    height[node] = h + 1;
    return height[node];
}

void dfs(int root){
    getHeight(root);
    for(int i: adj[root]){
        parent[i] = root;
        dfs(i);
    }
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    height.assign(n + 1, 0);
    parent.assign(n + 1, -1);
    vector<bool> seen(n + 1, 0);
    adj.resize(n + 1);
    for(int i = 0; i < n - 1; i++){
        int u, v;
        cin >> u >> v;
        if(seen[v])
            adj[v].push_back(u);
        else
            adj[u].push_back(v);
        seen[u] = seen[v] = 1;
    }
    dfs(1);
    for(int i = 1; i <= n; i++)
        cout << height[i] << " " << parent[i] << "\n";
    return 0;
}
