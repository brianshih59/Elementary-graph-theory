#include <bits/stdc++.h>
using namespace std;

int new_index = 0;
vector<vector<int>> adj;
vector<int> path;
vector<int> level;
vector<int> first_meet;
vector<int> log_table;
vector<vector<int>> sparse_table;
vector<pair<int, int>> query;
vector<int> ans;

void dfs(int v, int parent, int lev) {
    int index = new_index;
    ++new_index;
    level[index] = lev;
    first_meet[v] = path.size();
    path.push_back(index);
    for(int u: adj[v]) {
        if(u == parent)  continue;
        dfs(u, v, lev + 1);
        path.push_back(index);
    }
}

void RMQ(){
    int k = path.size();
    log_table.resize(k + 1);
    for(int i = 2; i < log_table.size(); ++i)
        log_table[i] = log_table[i / 2] + 1;
    sparse_table.resize(log_table.back() + 1, vector<int>(k));
    sparse_table[0] = path;
    for(int row = 1; row < sparse_table.size(); ++row)
        for(int i = 0; i <= k - (1 << row); ++i)
            sparse_table[row][i] = min(sparse_table[row - 1][i], sparse_table[row - 1][i + (1<<(row - 1))]);
}

int shortest_path(int l, int r) {
    int log = log_table[r - l];
    int lca = min(sparse_table[log][l], sparse_table[log][r - (1 << log)]);
    return level[path[l]] + level[path[r - 1]] - 2 * level[lca] ;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, Q;
    cin >> n;
    adj.resize(n);
    level.resize(n);
    first_meet.resize(n);
    for(int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        adj[--u].push_back(--v);
        adj[v].push_back(u);
    }
    dfs(0, -1, 1);
    RMQ();
    cin >> Q;
    ans.resize(Q);
    for(int i = 0; i < Q; ++i) {
        int u, v;
        cin >> u >> v;
        query.push_back({--u, --v});
    }
    for(int i = 0; i < Q; ++i) {
        int fm1 = first_meet[query[i].first];
        int fm2 = first_meet[query[i].second];
        if(fm1 > fm2)
            swap(fm1, fm2);
        ans[i] = shortest_path(fm1, fm2 + 1);
    }
    for(int i: ans)
        cout << i << "\n";
    return 0;
}
