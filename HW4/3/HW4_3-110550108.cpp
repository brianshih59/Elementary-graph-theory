#include <bits/stdc++.h>
#define pb push_back
using namespace std;

struct Edge{
    int to, cap, idx;   // idx用來找反向邊的idx
    Edge(int to, int cap, int idx): to(to), cap(cap), idx(idx){}
};

int n, m, k;
vector<int> bottleNeck; // 該點當前能通過的最大流量
vector<vector<Edge>> adj;
unordered_map<int, pair<int, int>> pre; // 紀錄回溯的路徑，first為parent，second為adj的idx

void bfs(int src, int des) {
    bottleNeck.assign(n + m + 3, 0);
    queue<int> q;
    q.push(src);
    bottleNeck[src] = INT_MAX;
    while(!q.empty()){
        int x = q.front();
        q.pop();
        for(int i = 0; i < adj[x].size(); i++){
            Edge e = adj[x][i];
            if(!bottleNeck[e.to] && e.cap > 0){ // 還沒走過且能通過
                pre[e.to] = {x, i};
                bottleNeck[e.to] = min(bottleNeck[x], e.cap);
                q.push(e.to);
            }
            if(e.to == des) // 抵達des
                break;
        }
    }
}

int Edmond_Karp(int src, int des) {
    int flow = 0;
    while(1){
        bfs(src, des);
        if(!bottleNeck[des])    // 走不到des
            break;
        int cur = des;
        while(cur != src){  // backtrack
            int prev = pre[cur].first, i = pre[cur].second;
            Edge& forward = adj[prev][i];
            Edge& backward = adj[forward.to][forward.idx];
            forward.cap -= bottleNeck[des];
            backward.cap += bottleNeck[des];
            cur = backward.to;
        }
        flow += bottleNeck[des];
    }
    return flow;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m >> k;
    adj.resize(n + m + 3);  // 前面加2個，後面加1個
    adj[0].pb(Edge(1, n + k, 0));
    adj[1].pb(Edge(0, 0, 0));
    for(int i = 0; i < n; i++){
        int t;
        cin >> t;
        for(int j = 0; j < t; j++){
            int k;
            cin >> k;
            adj[i + 2].pb(Edge(k + n + 1, 1, adj[k + n + 1].size()));
            adj[k + n + 1].pb(Edge(i + 2, 0, adj[i + 2].size() - 1));
        }
    }
    for(int i = 2; i < 2 + n; i++){
        adj[1].pb(Edge(i, 2, adj[i].size()));
        adj[i].pb(Edge(1, 0, adj[1].size() - 1));
    }
    for(int i = n + 2; i < n + 2 + m; i++){
        adj[i].pb(Edge(n + m + 2, 1, adj[n + m + 2].size()));
        adj[n + m + 2].pb(Edge(i, 0, adj[i].size() - 1));
    }
    int ans = Edmond_Karp(0, m + n + 2);
    cout << ans << '\n';
    return 0;
}
