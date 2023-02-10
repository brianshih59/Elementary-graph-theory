#include <bits/stdc++.h>
using namespace std;
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, m, p, q, t, T;
    cin >> n >> m >> p >> q >> t >> T;
    vector<pair<int, int>> adj[n + 1];
    vector<int> time(n + 1, INT_MAX);
    vector<bool> infected(n + 1, 0);
    for(int i = 0; i < m; i++){
        int a, b, w;
        cin >> a >> b >> w;
        adj[a].push_back({b, w});
    }
    queue<int> que;
    for(int i = 0; i < p; i++){
        int x;
        cin >> x;
        que.push(x);
        infected[x] = 1;
        time[x] = 0;
    }
    while(!que.empty()){
        int u = que.front();
        que.pop();
        for(auto &[v, w]: adj[u]){
            if(!infected[v]){
                time[v] = time[u] + w;
                infected[v] = 1;
                que.push(v);
            }
        }
    }
    // t 之前的必定為infected
    infected.assign(n + 1, 0);
    for(int i = 1; i <= n; i++){
        if(time[i] < t){
            infected[i] = 1;
            time[i] = 0;
            que.push(i);
        }
        else
            time[i] = INT_MAX;
    }
    vector<bool> protect(n + 1, 0);
    for(int i = 0; i < q; i++){
        int x;
        cin >> x;
        if(!infected[x]){
            protect[x] = 1;
            time[x] = 0;
            que.push(x);
        }
    }
    while(!que.empty()){
        int u = que.front();
        que.pop();
        for(auto &[v, w]: adj[u]){
            if(protect[u]){
                if(!protect[v] && time[u] + 1 <= time[v]){  // antivirus 早於 virus
                    time[v] = time[u] + 1;
                    protect[v] = 1;
                    infected[v] = 0;
                    que.push(v);
                }
            }
            else if(infected[u]){
                if(!infected[v] && time[u] + w < time[v]){  // virus 早於 antivirus
                    time[v] = time[u] + w;
                    infected[v] = 1;
                    protect[v] = 0;
                    que.push(v);
                }
            }
        }
    }
    int ans = 0;
    for(int i = 1; i <= n; i++)
        if(infected[i] && time[i] < T - t)
            ++ans;
    cout << ans;
    return 0;
}
