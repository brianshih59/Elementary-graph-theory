#include <bits/stdc++.h>
using namespace std;
int main()
{
    int n= 0;
    cin >> n;
    unordered_map<int, int> mp;
    pair<int, int> ans(0, 0);
    for(int i=0; i<n; i++){
        int num;
        cin >> num;
        mp[num]++;
        if(mp[num] > ans.second){
            ans.first = num;
            ans.second = mp[num];
        }
        else if(mp[num] == ans.second && num > ans.first)
            ans.first = num;
    }
    cout << ans.first << " " << ans.second << endl;
    return 0;
}
