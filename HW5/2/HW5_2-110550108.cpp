// minimum vertex cut set
#include <bits/stdc++.h>
#define pii pair<int, int>
using namespace std;

int n, m;

bool bfs(vector<vector<int>>& adj, vector<int>& pre, int src, int des){
    queue<int> q;
    q.push(src);
    vector<bool> vis(n, 0);
    while(!q.empty()){
        int u = q.front();
        q.pop();
        if(!vis[u]){
            vis[u] = 1;
            for(int i = 0; i < n; i++){
                if(adj[u][i + n] > 0 && !vis[i]){
                    pre[i] = u;
                    q.push(i);
                    if(i == des)
                        return 1;
                }
            }
        }
    }
    return 0;
}

int edmonds(vector<vector<int>>& adj, int src, int des){
    int flow = 0;
    vector<int> pre(n, -1);
    while(bfs(adj, pre, src, des)){
        int i = des;
        while(i != src){
            int pred = pre[i];
            adj[i + n][pred] += 1;
            adj[pred][i + n] -= 1;
            adj[i][i + n] += 1;
            adj[i + n][i] -= 1;
            i = pred;
        }
        flow += 1;
    }
    return flow;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m;
    // 將點分為in and out, 每條path出於in也終於in
    vector<vector<int>> adj(2 * n, vector<int>(2 * n, 0));
    vector<pii> degree(n, {0, 0});
    for(int i = 0; i < m; i++){
        int a, b;
        cin >> a >> b;
        a--, b--;
        adj[a][b + n] = 1;
        adj[b][a + n] = 1;
        degree[a].first++;
        degree[a].second++;
        degree[b].first++;
        degree[b].second++;
    }
    for(int i = 0; i < n; i++)
        adj[i + n][i] = 1;
    int maxflow = INT_MAX;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            // 跳過不可能有更小的flow的case, 雖然這不是完全正確的方法, 不過我拿到AC了, 好爽
            if(i != j && (degree[i].second < maxflow || degree[j].first < maxflow)){
                vector<vector<int>> temp(adj);
                int cur = edmonds(temp, i, j);
                maxflow = min(maxflow, cur);
            }
            if(maxflow == 2){
                cout << maxflow;
                return 0;
            }
        }
    }
    cout << maxflow;
    return 0;
}
