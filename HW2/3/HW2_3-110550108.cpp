#include <bits/stdc++.h>
using namespace std;
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, m;
    cin >> n;
    vector<vector<int>> adj(n);
    vector<int> deg(n, 0);
    for(int i = 1; i < n; i++){
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
        ++deg[u], ++deg[v];
    }

    cin >> m;
    vector<int> key(m);
    for(int i = 0; i < m; i++)
        cin >> key[i];

    queue<int> q;
    vector<int> dis_to_joint(n, 0), new_deg(n, 2);
    for(int i = 0; i < n; i++){
        if(deg[i] == 1){
            q.push(i);
            dis_to_joint[i] = 1;
            new_deg[i] = 1;
        }
        else if(deg[i] == 3)
            new_deg[i] = 3;
    }
    while(!q.empty()){
        int v = q.front();
        q.pop();
        for(int u: adj[v]){
            if(new_deg[u] != 1){    // 避免往回到leaf
                --deg[v], --deg[u];
                if(new_deg[u] == 2){
                    new_deg[u] = 1;
                    dis_to_joint[u] = dis_to_joint[v] + 1;
                    q.push(u);
                }
            }
        }
    }
    vector<int> outer_joint;
    for(int i = 0; i < n; i++)
        if(deg[i] < 2 && new_deg[i] == 3)
            outer_joint.push_back(i);

    for(int i = 0; i < 2; i++){ // 正反2種
        vector<int> vertical_bars;
        q.push(outer_joint[i]);
        int prev = -1;
        while(!q.empty()){
            int v = q.front();
            q.pop();
            for(int u: adj[v]){
                if(u == prev)
                    continue;
                if(new_deg[u] == 1){
                    vertical_bars.push_back(dis_to_joint[u]);
                    continue;
                }
                q.push(u);
            }
            prev = v;
        }
        bool flag = 0;
        if(vertical_bars.size() == m + 2 && (vertical_bars[0] == key[0] || vertical_bars[1] == key[0]) && (vertical_bars[m] == key[m - 1] || vertical_bars[m + 1] == key[m - 1])){
            // 因為頭尾各有兩種，所以要+2
            flag = 1;
            for(int i = 1; i < m - 1; i++){ // 核對中間
                if(key[i] != vertical_bars[i + 1]){
                    flag = 0;
                    break;
                }
            }
        }
        if(flag){
            cout << "YES";
            return 0;
        }
    }
    cout << "NO";
    return 0;
}
