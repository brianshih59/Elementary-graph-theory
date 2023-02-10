#include <bits/stdc++.h>
using namespace std;
#define ll long long
int findMinPos(vector<int>& deg, int i, int l, int r){
    int pos = i;
    while (l <= r) {
        int m = l + (r - l) / 2;
        if (deg[m] >= i){
            pos = m;
            l = m + 1;
        }
        else
            r = m - 1;
    }
    return pos;
}
bool erdos_gallai(vector<int>& deg, vector<ll>& right_sum, int n){
    sort(deg.begin() + 1, deg.end(), greater<int>());
    for(int i=n; i>0; i--)
        right_sum[i] = right_sum[i+1] + deg[i];
    ll left = 0, right;
    for(int i=1; i<=n; i++){
        left += deg[i];
        int pos = findMinPos(deg, i, i + 1, n);
        right = (ll)i * (pos - 1) + right_sum[pos + 1];
        if (left > right)
            return 0;
    }
    return 1;
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int Q;
    cin >> Q;
    while(Q--){
        int n, m;
        ll sum = 0;
        bool flag = 1;
        cin >> n >> m;
        vector<int> deg(n + 1, 0);
        vector<long long> right_sum(n + 2, 0);
        for(int i=1; i<=n; i++){
            cin >> deg[i];
            sum += deg[i];
        }
        if(sum & 1)
            flag = 0;
        for(int i=0; i<m; i++){
            int u, v;
            cin >> u >> v;
            --deg[u];
            --deg[v];
            if(deg[u] < 0 || deg[v] < 0)
                flag = 0;
        }
        if(flag)
            cout << (erdos_gallai(deg, right_sum, n) ? "Yes" : "No") << "\n";
        else
            cout << "No\n";
    }
    return 0;
}
