#include <bits/stdc++.h>
#define ll long long
#define pii pair<ll, int>

using namespace std;

int n, m;

ll dijkstra(vector<vector<pii>>& adj, int src, int des) {
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    vector<ll> dis(n, INT_MAX);
    vector<bool> vis(n, 0);
    pq.push({0, src});
    dis[src] = 0;
    while(!pq.empty()){
        int u = pq.top().second;
        pq.pop();
        if(vis[u])
            continue;
        vis[u] = 1;
        for(auto& [v, w]: adj[u]){
            if(!vis[v] && dis[u] + w < dis[v]){
                dis[v] = dis[u] + w;
                pq.push({dis[v], v});
            }
        }
    }
    return dis[des];
}

int main() {
    cin >> n >> m;
    vector<vector<vector<pii>>> adjs;
    vector<vector<pii>> adj(n);
    for(int i = 0; i < m; i++){
        int u, v, w;
        cin >> u >> v >> w;
        u--, v--;
        vector<vector<pii>> tmp(adj);
        bool flag = 0;
        for(auto& [u2, w2]: tmp[v]){
            if(u2 == u && w < w2){
                w2 = w;
                flag = 1;
            }
        }
        if(!flag)
            tmp[v].push_back({u, w});
        adj[u].push_back({v, w});
        for(int j = 0; j < adjs.size(); j++)
            adjs[j][u].push_back({v, w});
        adjs.push_back(tmp);
    }
    ll ans = dijkstra(adj, 0, 1);
    for(int i = 0; i < m; i++){
        ll cur = dijkstra(adjs[i], 0, 1);
        if(cur < ans)
            cout << "HAPPY" << '\n';
        else if(cur > ans)
            cout << "SAD" << '\n';
        else
            cout << "SOSO" << '\n';
    }
    return 0;
}
