#include <bits/stdc++.h>
using namespace std;
int main()
{
    int n, a, b, c;
    cin >> n >> a >> b >> c;
    int m[n][n], points[n];
    for(int i=0; i<n; i++){
        points[i] = 0;
        for(int j=0; j<n; j++)
            cin >> m[i][j];
    }
    for(int i=0; i<n; i++){
        for(int j=i+1; j<n; j++){
            if(m[i][j] == 0){
                points[i] += b;
                points[j] += a;
            }
            else if(m[i][j] == 1){
                points[i] += a;
                points[j] += b;
            }
            else{
                points[i] += c;
                points[j] += c;
            }
        }
    }
    for(auto i: points)
        cout << i << " ";
    return 0;
}
