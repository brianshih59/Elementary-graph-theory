#include<bits/stdc++.h>
using namespace std;
void cal_time(vector<vector<int>>& adj, vector<int>& time, int i){
    vector<int> temp;
    for(int j: adj[i]){
        if(time[j] == INT_MAX){
            time[j] = time[i] + 1;
            temp.push_back(j);
        }
        else if(time[i] + 1 < time[j])
            time[j] = time[i] + 1;
    }
    for(int u: temp)
        cal_time(adj, time, u);
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m, k, t;
    cin >> n >> m >> k >> t;
    if(!t){
        cout << 0;
        return 0;
    }
    vector<vector<int>> adj(n+1);
    vector<int> time(n+1, INT_MAX);
    while(m--){
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
    }
    while(k--){
        int j;
        cin >> j;
        time[j] = 0;
    }
    for(int i=1; i<=n; i++)
        if(time[i] != INT_MAX)
            cal_time(adj, time, i);
    int cnt = 0;
    for(int i: time)
        if(i < t)
            cnt++;
    cout << cnt;
    return 0;
}
