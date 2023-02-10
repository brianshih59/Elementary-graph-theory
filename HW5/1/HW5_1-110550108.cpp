#include <bits/stdc++.h>
#define pii pair<int, int>

using namespace std;

int main(){
    int Q;
    cin >> Q;
    while(Q--){
        int n, m;
        cin >> n >> m;
        vector<pii> edges;
        for(int i = 0; i < m; i++){
            int x, y;
            cin >> x >> y;
            x--, y--;
            edges.push_back({x, y});
        }
        bool ans = 0;
        for(int i = 1; i < (1 << m); i++){
            int x = i;
            vector<bool> include(m, 0);
            for(int j = 0; j < m; j++){
                include[j] = x % 2;
                x >>= 1;
                if(!x)
                    break;
            }
            if(count(include.begin(), include.end(), 1) < 9)
                continue;
            vector<vector<int>> adj(n);
            for(int j = 0; j < m; j++){
                if(include[j]){
                    adj[edges[j].first].push_back(edges[j].second);
                    adj[edges[j].second].push_back(edges[j].first);
                }
            }
            for(int j = 0; j < n; j++){
                if(adj[j].size() == 2){
                    vector<int> tmp;
                    for(int k: adj[j]){
                        auto iter = remove(adj[k].begin(), adj[k].end(), j);
                        adj[k].erase(iter, adj[k].end());
                        tmp.push_back(k);
                    }
                    if(find(adj[tmp[0]].begin(), adj[tmp[0]].end(), tmp[1]) != adj[tmp[0]].end())
                        continue;
                    adj[tmp[0]].push_back(tmp[1]);
                    adj[tmp[1]].push_back(tmp[0]);
                    adj[j].clear();
                }
            }
            int cnt = 0;
            for(int j = 0; j < n; j++)
                if(!adj[j].empty())
                    cnt++;
            bool flag = 0;
            if(cnt == 5){
                for(int j = 0; j < n; j++){
                    if(adj[j].size() != 4 && adj[j].size() != 0){
                        flag = 1;
                        break;
                    }
                }
                if(!flag){
                    cout << "No" << '\n';
                    ans = 1;
                    break;
                }
            }
            else if(cnt == 6){
                for(int j = 0; j < n; j++){
                    if(adj[j].size() != 3 && adj[j].size() != 0){
                        flag = 1;
                        break;
                    }
                }
                if(flag)
                    continue;
                unordered_set<int> s1, s2;
                for(int j = 0; j < n; j++){
                    if(adj[j].empty())
                        continue;
                    if(s1.empty() && s2.empty()){
                        s1.insert(j);
                        for(int k: adj[j])
                            s2.insert(k);
                        continue;
                    }
                    if(s2.find(j) == s2.end()){
                        for(int k: adj[j]){
                            if(s2.find(k) == s2.end()){
                                flag = 1;
                                break;
                            }
                        }
                    }
                    else{
                        for(int k: adj[j]){
                            if(s2.find(k) != s2.end()){
                                flag = 1;
                                break;
                            }
                        }
                    }
                }
                if(!flag){
                    cout << "No" << '\n';
                    ans = 1;
                    break;
                }
            }
        }
        if(!ans)
            cout << "Yes" << '\n';
    }
    return 0;
}
