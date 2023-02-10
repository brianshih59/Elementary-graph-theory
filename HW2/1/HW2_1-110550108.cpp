#include <bits/stdc++.h>
#define inf 1e9
using namespace std;
int cal_dis(string s, string t){
    for(int i=min(s.size(), t.size()); i>=0; i--)
        if(s.substr(s.size() - i) == t.substr(0, i))
            return t.size() - i;
    return t.size();
}
string combine(string s, string t){
    for(int i=min(s.size(), t.size()); i>=0; i--)
        if(s.substr(s.size() - i) == t.substr(0, i))
            return s + t.substr(i);
    return s + t;
}
bool isSubstring(string s, string t){
    for(int i=0; i<=(int)s.size() - (int)t.size(); i++){
        if(s.substr(i, t.size()) == t)
            return 1;
    }
    return 0;
}
bool comp(vector<string>& strs, vector<vector<int>>& paths, int cur, int shortest, int k){
    for(int i=0; i<k; i++){
        if(strcmp(strs[paths[cur][i]].c_str(), strs[paths[shortest][i]].c_str()) == 0)
            continue;
        return strcmp(strs[paths[cur][i]].c_str(), strs[paths[shortest][i]].c_str()) < 0;
    }
    return 0;
}
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    vector<string> strs(n);
    for(int i=0; i<n; i++)
        cin >> strs[i];
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            if(i != j && isSubstring(strs[i], strs[j])) strs[j] = "";
    sort(strs.begin(), strs.end());
    vector<vector<int>> dis(n, vector<int>(n, 0));
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            if(i != j)  dis[i][j] = cal_dis(strs[i], strs[j]);
    int m = (1 << n);
    vector<vector<int>> dp(m, vector<int>(n, inf));
    vector<vector<int>> parent(m, vector<int>(n, -1));
    for(int i=0; i<n; i++)
        dp[1<<i][i] = strs[i].size();
    for(int mask=0; mask<m; mask++){
        for(int bit=0; bit<n; bit++){
            if((mask & (1<<bit)) == 0)  continue;
            int pre_mask = mask ^ (1<<bit);
            for(int i=0; i<n; i++){
                if((pre_mask & (1<<i)) == 0)  continue;
                if(dp[pre_mask][i] + dis[i][bit] <= dp[mask][bit]){
                    dp[mask][bit] = dp[pre_mask][i] + dis[i][bit];
                    parent[mask][bit] = i;
                }
            }
        }
    }
    int path_len = inf;
    vector<int> possible_end;
    for(int i=0; i<n; i++){
        if(dp[m - 1][i] <= path_len) {
            path_len = dp[m - 1][i];
            possible_end.push_back(i);
        }
    }
    int k = possible_end.size();
    vector<vector<int>> paths(k);
    for(int i=0; i<k; i++)
        paths[i].push_back(possible_end[i]);
    for(int i=0; i<k; i++){
        int mask = m - 1;
        int start = paths[i][0];
        while(parent[mask][start] != -1){
            int next = parent[mask][start];
            paths[i].push_back(next);
            mask ^= (1 << start);
            start = next;
        }
    }
    for(int i=0; i<k; i++)
        reverse(paths[i].begin(), paths[i].end());
    int shortest = 0;
    for(int i=1; i<k; i++)
        if(comp(strs, paths, i, shortest, k))
            shortest = i;
    string res = strs[paths[shortest][0]];
    for(int i=1; i<n; i++)
        res = combine(res, strs[paths[shortest][i]]);
    cout << res;
    return 0;
}
